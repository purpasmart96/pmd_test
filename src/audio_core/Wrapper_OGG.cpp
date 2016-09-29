#include "../header/Wrapper_OGG.h"
#include "../header/SoundObject.h"

#include "../../Utils/header/Logger.h"

#ifdef _MSC_VER	
	#pragma comment(lib, "libogg.lib")
	#pragma comment(lib, "libvorbis.lib")
	#pragma comment(lib, "libvorbisfile.lib")
#endif

#include <vorbis/vorbisfile.h>
#include <vorbis/codec.h>

#include <ogg/os_types.h>
#include <ogg/ogg.h>

#include <string.h>
#include <climits>

//using namespace MySound;




size_t AR_readOgg(void* dst, size_t size1, size_t size2, void* fh)
{
    ogg_file* of = reinterpret_cast<ogg_file*>(fh);
    size_t len = size1 * size2;
    if ( of->curPtr + len > of->filePtr + of->fileSize )
    {
        len = of->filePtr + of->fileSize - of->curPtr;
    }
    memcpy( dst, of->curPtr, len );
    of->curPtr += len;
    return len;
}

int AR_seekOgg( void *fh, ogg_int64_t to, int type ) {
    ogg_file* of = reinterpret_cast<ogg_file*>(fh);

    switch( type ) {
        case SEEK_CUR:
            of->curPtr += to;
            break;
        case SEEK_END:
            of->curPtr = of->filePtr + of->fileSize - to;
            break;
        case SEEK_SET:
            of->curPtr = of->filePtr + to;
            break;
        default:
            return -1;
    }
    if ( of->curPtr < of->filePtr ) {
        of->curPtr = of->filePtr;
        return -1;
    }
    if ( of->curPtr > of->filePtr + of->fileSize ) {
        of->curPtr = of->filePtr + of->fileSize;
        return -1;
    }
    return 0;
}

int AR_closeOgg(void* fh)
{
    return 0;
}

long AR_tellOgg(void *fh )
{
    ogg_file* of = reinterpret_cast<ogg_file*>(fh);
    return (of->curPtr - of->filePtr);
}

static ov_callbacks callbacks_ogg;

WrapperOgg::WrapperOgg(int minDecompressLengthAtOnce)
{
	callbacks_ogg.read_func = AR_readOgg;
	callbacks_ogg.seek_func = AR_seekOgg;
	callbacks_ogg.close_func = AR_closeOgg;
	callbacks_ogg.tell_func = AR_tellOgg;

	this->ov = NULL;
	this->minDecompressLengthAtOnce = minDecompressLengthAtOnce;
	if (this->minDecompressLengthAtOnce == -1)
	{
		this->minDecompressLengthAtOnce = INT_MAX;
	}
	else 
	{
		if (this->minDecompressLengthAtOnce % OGG_BUFFER_SIZE != 0)
		{
			MyUtils::Logger::LogError("OGG buffer size and OpenAL buffer size are not modulable !!");
			MyUtils::Logger::LogError("this->minDecompressLengthAtOnce % OGG_BUFFER_SIZE != 0");
		}
	}

}


WrapperOgg::~WrapperOgg()
{
	ov_clear(ov);
	SAFE_DELETE(ov);
}


void WrapperOgg::LoadFromMemory(char * data, int dataSize, SoundInfo * soundInfo)
{
	//http://stackoverflow.com/questions/13437422/libvorbis-audio-decode-from-memory-in-c	
	
	
	this->t.curPtr = this->t.filePtr = data;
	this->t.fileSize = dataSize;
				
	this->ov = new OggVorbis_File;	
	memset( ov, 0, sizeof( OggVorbis_File ) );
	int ret = ov_open_callbacks((void *)&this->t, this->ov, NULL, -1, callbacks_ogg);
	
	vorbis_info * vi = ov_info(this->ov, -1);
	memset(soundInfo, 0, sizeof(SoundInfo));

	soundInfo->channels = vi->channels;
	soundInfo->bitrate_lower = vi->bitrate_lower;
	soundInfo->bitrate_nominal = vi->bitrate_nominal;
	soundInfo->bitrate_upper = vi->bitrate_upper;
	soundInfo->bitrate_window = vi->bitrate_window;
	soundInfo->freqency = vi->rate;
	soundInfo->bitsPerChannel = 16;
    
    if(ov_seekable(this->ov) == 0)
    {
        // Disable seeking
        soundInfo->seekable = false;
        this->seekable = false;
    }
    else
    {
        soundInfo->seekable = true;
        this->seekable = true;
    }
				
}

void WrapperOgg::LoadFromFile(FILE * f, SoundInfo * soundInfo)
{
	
	this->ov = new OggVorbis_File;	
	memset( ov, 0, sizeof( OggVorbis_File ) );
	
	//int ret = ov_open(f, this->ov, NULL, 0); // buggy
	int ret = ov_open_callbacks(f, this->ov, NULL, -1, OV_CALLBACKS_DEFAULT);

	
	vorbis_info * vi = ov_info(this->ov, -1);
	memset(soundInfo, 0, sizeof(SoundInfo));

	soundInfo->channels = vi->channels;
	soundInfo->bitrate_lower = vi->bitrate_lower;
	soundInfo->bitrate_nominal = vi->bitrate_nominal;
	soundInfo->bitrate_upper = vi->bitrate_upper;
	soundInfo->bitrate_window = vi->bitrate_window;
	soundInfo->freqency = vi->rate;
	soundInfo->bitsPerChannel = 16;
    
    if(ov_seekable(this->ov) == 0)
    {
        // Disable seeking
        soundInfo->seekable = false;
        this->seekable = false;
    }
    else
    {
        soundInfo->seekable = true;
        this->seekable = true;
    }
}

void WrapperOgg::ResetStream()
{
	
    if (this->seekable)
    {
        int err = ov_raw_seek(this->ov, 0);
        if (err != 0)
        {
            MyUtils::Logger::LogError("ov_raw_seek err: %i", err);
        }
    }
}

void WrapperOgg::Seek(size_t pos, SEEK_POS start)
{
	if (this->seekable == false)
	{
		return;
	}

	if (start == SEEK_POS::START)
	{
		this->ResetStream();
	}

	int err = ov_raw_seek(this->ov, pos);
	if (err != 0)
	{
		MyUtils::Logger::LogError("ov_raw_seek err: %i", err);
	}
	
}

size_t WrapperOgg::GetCurrentStreamPos() const
{
	return ov_raw_tell(this->ov);
}

float WrapperOgg::GetTime() const
{
	return static_cast<float>(ov_time_tell(this->ov));
}

float WrapperOgg::GetTotalTime() const
{
	return static_cast<float>(ov_time_total(this->ov, -1));
}

void WrapperOgg::DecompressAll(std::vector<char> & decompressBuffer)
{
	char bufArrayBckp[OGG_BUFFER_SIZE];
	memcpy(bufArrayBckp, this->bufArray, sizeof(char) * OGG_BUFFER_SIZE);


	size_t pos = this->GetCurrentStreamPos();
	this->ResetStream();


	decompressBuffer.clear();

	int endian = 0;   // 0 for Little-Endian, 1 for Big-Endian
	int bitStream;
	long bytes;
	//int c = 0;



	do
	{
		// Read up to a buffer's worth of decoded sound data
		bytes = ov_read(this->ov, this->bufArray, OGG_BUFFER_SIZE, endian, 2, 1, &bitStream);

		if (bytes < 0)
		{
			MyUtils::Logger::LogError("OGG stream ov_read error - returned %i", bytes);
			continue;
		}

		// Append to end of buffer
		decompressBuffer.insert(decompressBuffer.end(), this->bufArray, this->bufArray + bytes);

	} while (bytes > 0);



	this->Seek(pos, ISoundFileWrapper::SEEK_POS::START);

	memcpy(this->bufArray, bufArrayBckp, sizeof(char) * OGG_BUFFER_SIZE);

}

void WrapperOgg::DecompressStream(std::vector<char> & decompressBuffer, bool inLoop)
{
	decompressBuffer.clear();

	int endian = 0;   // 0 for Little-Endian, 1 for Big-Endian
	int bitStream;
	long bytes;	
	//int c = 0;

	

	do
	{
		do 
		{		
			// Read up to a buffer's worth of decoded sound data
			bytes = ov_read(this->ov, this->bufArray, OGG_BUFFER_SIZE, endian, 2, 1, &bitStream);

            if(bytes < 0)
            {
                MyUtils::Logger::LogError("OGG stream ov_read error - returned %i", bytes);
                continue;
            }
            
			// Append to end of buffer
			decompressBuffer.insert(decompressBuffer.end(), this->bufArray, this->bufArray + bytes);

			if (static_cast<int>(decompressBuffer.size()) >= this->minDecompressLengthAtOnce)
			{
				return;
			}
			

		} while (bytes > 0);

		if (inLoop)
		{
			this->ResetStream();
		}
	
		if (this->minDecompressLengthAtOnce == INT_MAX)
		{
			return;
		}

	} while(inLoop);

	
}