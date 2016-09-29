// Copyright(c) 2015 Purpasmart
// The MIT License
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.


#include "util.h"
#include "common/vec.h"

#include "game_common/display_manager.h"
#include "game_common/controls_manager.h"
#include "game_common/game_manager.h"


#define S_COLOR_WHITE "^7"
#define COLOR_WHITE	  '7'
#define ColorIndex(c) (((c) - '0' ) & 7)

#define Q_COLOR_ESCAPE	'^'
#define Q_IsColorString(p) ( p && *(p) == Q_COLOR_ESCAPE && *((p) + 1) && *((p) + 1) != Q_COLOR_ESCAPE )


/*
============
Cvar_CommandCompletion
============
*/
/*
void Cvar_CommandCompletion(void(*callback)(const char *s))
{
    for (Cvar *cvar = cvar_vars; cvar; cvar = cvar->next)
    {
         callback(cvar->name);
    }
}
*/

/*
============
Cvar_Get
If the variable already exists, the value will not be set unless CVAR_ROM
The flags will be or'ed in if the variable exists.
============
*/
/*
Cvar *Cvar_Get(const char *var_name, const char *var_value, int flags)
{
    Cvar *var;
    long hash;

    if (!var_name || !var_value)
    {
        ERROR("Cvar_Get: NULL parameter\n");
    }

    if (!Cvar_ValidateString(var_name))
    {
        printf("invalid cvar name string: %s\n", var_name);
        var_name = "BADNAME";
    }

#if 0 // FIXME: values with backslash happen
    if (!Cvar_ValidateString(var_value)) {
        Com_Printf("invalid cvar value string: %s\n", var_value);
        var_value = "BADVALUE";
    }
#endif

    var = Cvar_FindVar(var_name);
    if (var)
    {
        // if the C code is now specifying a variable that the user already
        // set a value for, take the new value as the reset value
        if ((var->flags & CVAR_USER_CREATED) && !(flags & CVAR_USER_CREATED) && var_value[0])
        {
            var->flags &= ~CVAR_USER_CREATED;
            Z_Free(var->reset_string);
            var->reset_string = CopyString(var_value);

            // ZOID--needs to be set so that cvars the game sets as 
            // SERVERINFO get sent to clients
            cvar_modifiedFlags |= flags;
        }

        var->flags |= flags;
        // only allow one non-empty reset string without a warning
        if (!var->reset_string[0])
        {
            // we don't have a reset string yet
            Z_Free(var->reset_string);
            var->reset_string = CopyString(var_value);
        }
        else if (var_value[0] && strcmp(var->reset_string, var_value))
        {
            DEBUG("Warning: cvar \"%s\" given initial values: \"%s\" and \"%s\"\n",
                var_name, var->reset_string, var_value);
        }
        // if we have a latched string, take that value now
        if (var->latched_string)
        {
            char *s;

            s = var->latched_string;
            var->latched_string = NULL;	// otherwise cvar_set2 would free it
            Cvar_Set2(var_name, s, true);
            Z_Free(s);
        }

        // use a CVAR_SET for rom sets, get won't override
#if 0
        // CVAR_ROM always overrides
        if (flags & CVAR_ROM) {
            Cvar_Set2(var_name, var_value, qtrue);
        }
#endif
        return var;
    }

    //
    // allocate a new cvar
    //
    if (cvar_numIndexes >= MAX_CVARS)
    {
        ERROR("MAX_CVARS");
    }
    var = &cvar_indexes[cvar_numIndexes];
    cvar_numIndexes++;

    //var->name = CopyString(var_name);
    //var->string = CopyString(var_value);
    strlcpy(var->name, var_name, strlen(var_name));
    strlcpy(var->string, var_value, strlen(var_value));
    var->modified = true;
    var->modification_count = 1;
    var->value = atof(var->string);
    var->integer = atoi(var->string);
    //var->reset_string = CopyString(var_value);

    // link the variable in
    var->next = cvar_vars;
    cvar_vars = var;

    var->flags = flags;

    hash = generateHashValue(var_name);
    var->hash_next = hashTable[hash];
    hashTable[hash] = var;

    return var;
}
*/

/*
============
Cvar_Set2
============
*/
/*
Cvar *Cvar_Set2(const char *var_name, const char *value, bool force)
{
    Cvar *var;

    printf("Cvar_Set2: %s %s\n", var_name, value);

    if (!Cvar_ValidateString(var_name))
    {
        printf("invalid cvar name string: %s\n", var_name);
        var_name = "BADNAME";
    }

#if 0	// FIXME
    if (value && !Cvar_ValidateString(value)) {
        Com_Printf("invalid cvar value string: %s\n", value);
        var_value = "BADVALUE";
    }
#endif

    var = Cvar_FindVar(var_name);
    if (!var)
    {
        if (!value)
        {
            return NULL;
        }
        // create it
        if (!force)
        {
            return Cvar_Get(var_name, value, CVAR_USER_CREATED);
        }
        else
        {
            return Cvar_Get(var_name, value, 0);
        }
    }

    if (!value)
    {
        value = var->reset_string;
    }

    if (!strcmp(value, var->string))
    {
        return var;
    }
    // note what types of cvars have been modified (userinfo, archive, serverinfo, systeminfo)
    cvar_modifiedFlags |= var->flags;

    if (!force)
    {
        if (var->flags & CVAR_ROM)
        {
            printf("%s is read only.\n", var_name);
            return var;
        }

        if (var->flags & CVAR_INIT)
        {
            printf("%s is write protected.\n", var_name);
            return var;
        }

        if (var->flags & CVAR_LATCH)
        {
            if (var->latched_string)
            {
                if (strcmp(value, var->latched_string) == 0)
                    return var;
                Z_Free(var->latched_string);
            }
            else
            {
                if (strcmp(value, var->string) == 0)
                    return var;
            }

            printf("%s will be changed upon restarting.\n", var_name);
            var->latched_string = CopyString(value);
            var->modified = true;
            var->modification_count++;
            return var;
        }

        if ((var->flags & CVAR_CHEAT) && !cvar_cheats->integer)
        {
            printf("%s is cheat protected.\n", var_name);
            return var;
        }

    }
    else
    {
        if (var->latched_string)
        {
            Z_Free(var->latched_string);
            var->latched_string = NULL;
        }
    }

    if (!strcmp(value, var->string))
        return var;	// not changed

    var->modified = true;
    var->modification_count++;

    Z_Free(var->string); // free the old value string

    var->string = CopyString(value);
    var->value = atof(var->string);
    var->integer = atoi(var->string);

    return var;
}

*/


/*
============
Cvar_Set
============
*/
/*
void Cvar_Set(const char *var_name, const char *value)
{
    Cvar_Set2(var_name, value, true);
}
*/




/*
============
Cvar_Command
Handles variable inspection and changing from the console
============
*/
/*
bool Cvar_Command(void)
{
    Cvar *v;

    // check variables
    v = Cvar_FindVar(Cmd_Argv(0));
    if (!v)
    {
        return false;
    }

    // perform a variable print or set
    if (Cmd_Argc() == 1)
    {
        printf("\"%s\" is:\"%s" S_COLOR_WHITE "\" default:\"%s" S_COLOR_WHITE "\"\n", v->name, v->string, v->reset_string);
        if (v->latched_string)
        {
            printf("latched: \"%s\"\n", v->latched_string);
        }
        return true;
    }

    // set the value if forcing isn't required
    Cvar_Set2(v->name, Cmd_Argv(1), false);
    return true;
}
*/








int g_console_field_width = 78;


#define	NUM_CON_TIMES 4

#define	CON_TEXTSIZE 32768

typedef struct
{
    bool initialized;

    short text[CON_TEXTSIZE];
    int	current_line;   // line where next message will be printed
    int	x;              // offset in current line for next print
    int display;        // bottom of console displays this line

    int line_width;	    // characters across screen
    int total_lines;    // total lines in console scrollback
    float x_adjust;	    // for wide aspect screens

    float display_frac;	// aproaches finalFrac at scr_conspeed
    float final_frac;   // 0.0 to 1.0 lines of console to display

    int	vis_lines;      // in scanlines

    int	times[NUM_CON_TIMES];	// cls.realtime time the line was generated
    // for transparent notify lines
    vec4 color;
} Console;

//extern console_t con;

//console_t con;

Cvar *con_con_speed;
Cvar *con_notify_time;

#define	DEFAULT_CONSOLE_WIDTH 78

vec4 console_color = { 1.0, 1.0, 1.0, 1.0 };




/*
================
Con_ClearNotify
================
*/
void Con_ClearNotify(Console *self)
{
    for (int i = 0; i < NUM_CON_TIMES; i++)
    {
        self->times[i] = 0;
    }
}



/*
================
Con_CheckResize
If the line width has changed, reformat the buffer.
================
*/
void Con_CheckResize(Console *self)
{
    int	i, j, width, old_width, old_total_lines, num_lines, num_chars;
    static short tbuf[CON_TEXTSIZE];

    width = (1280 / 8) - 2;

    if (width == self->line_width)
        return;

    if (width < 1) // video hasn't been initialized yet
    {
        width = DEFAULT_CONSOLE_WIDTH;
        self->line_width = width;
        self->total_lines = CON_TEXTSIZE / self->line_width;
        for (i = 0; i < CON_TEXTSIZE; i++)

            self->text[i] = (ColorIndex(COLOR_WHITE) << 8) | ' ';
    }
    else
    {
        old_width = self->line_width;
        self->line_width = width;
        old_total_lines = self->total_lines;
        self->total_lines = CON_TEXTSIZE / self->line_width;
        num_lines = old_total_lines;

        if (self->total_lines < num_lines)
            num_lines = self->total_lines;

        num_chars = old_width;

        if (self->line_width < num_chars)
            num_chars = self->line_width;

        memcpy(tbuf, self->text, CON_TEXTSIZE * sizeof(short));
        for (i = 0; i < CON_TEXTSIZE; i++)

            self->text[i] = (ColorIndex(COLOR_WHITE) << 8) | ' ';


        for (i = 0; i < num_lines; i++)
        {
            for (j = 0; j < num_chars; j++)
            {
                self->text[(self->total_lines - 1 - i) * self->line_width + j] =
                      tbuf[((self->current_line - i + old_total_lines) % old_total_lines) * old_width + j];
            }
        }

        Con_ClearNotify(self);
    }

    self->current_line = self->total_lines - 1;
    self->display = self->current_line;
}

/*
================
Con_Init
================
*/
/*
void Con_Init(void)
{
    con_notify_time = Cvar_Get("con_notifytime", "3", 0);
    con_con_speed = Cvar_Get("scr_conspeed", "3", 0);

    Field_Clear(&g_consoleField);
    g_consoleField.widthInChars = g_console_field_width;
    for (int i = 0; i < COMMAND_HISTORY; i++)
    {
        Field_Clear(&historyEditLines[i]);
        historyEditLines[i].widthInChars = g_console_field_width;
    }

    Cmd_AddCommand("toggleconsole", Con_ToggleConsole_f);
    Cmd_AddCommand("messagemode", Con_MessageMode_f);
    Cmd_AddCommand("messagemode2", Con_MessageMode2_f);
    Cmd_AddCommand("messagemode3", Con_MessageMode3_f);
    Cmd_AddCommand("messagemode4", Con_MessageMode4_f);
    Cmd_AddCommand("clear", Con_Clear_f);
    Cmd_AddCommand("condump", Con_Dump_f);
}
*/

/*
===============
Con_Linefeed
===============
*/
void Con_Linefeed(Console *self, bool skip_notify)
{
    // mark time for transparent overlay
    if (self->current_line >= 0)
    {
        if (skip_notify)
        {
            self->times[self->current_line % NUM_CON_TIMES] = 0;
        }
        else
        {
            //self->times[self->current_line % NUM_CON_TIMES] = cls.realtime;
        }
    }

    self->x = 0;
    if (self->display == self->current_line)
        self->display++;
    self->current_line++;
    for (int i = 0; i < self->line_width; i++)
    {
        self->text[(self->current_line % self->total_lines) * self->line_width + i] = (ColorIndex(COLOR_WHITE) << 8) | ' ';
    }
}

/*
================
CL_ConsolePrint
Handles cursor positioning, line wrapping, etc
All console printing must go through this in order to be logged to disk
If no console is visible, the text will appear at the top of the game window
================
*/
void CL_ConsolePrint(Console *self, char *txt)
{
    int		y;
    int		c, l;
    int		color;
    bool skip_notify = false;  // NERVE - SMF
    int prev;                // NERVE - SMF

    // TTimo - prefix for text that shows up in console but not in notify
    // backported from RTCW
    if (!strncmp(txt, "[skip_notify]", 13))
    {
        skip_notify = true;
        txt += 12;
    }

    // for some demos we don't want to ever show anything on the console
    //if (cl_noprint && cl_noprint->integer)
    //{
    //    return;
    //}

    if (!self->initialized)
    {
        self->color.v[0] =
        self->color.v[1] =
        self->color.v[2] =
        self->color.v[3] = 1.0f;
        self->line_width = -1;
        Con_CheckResize(self);
        self->initialized = true;
    }

    color = ColorIndex(COLOR_WHITE);

    while ((c = *txt) != 0)
    {
        if (Q_IsColorString(txt))
        {
            color = ColorIndex(*(txt + 1));
            txt += 2;
            continue;
        }

        // count word length
        for (l = 0; l< self->line_width; l++)
        {
            if (txt[l] <= ' ')
            {
                break;
            }
        }

        // word wrap
        if (l != self->line_width && (self->x + l >= self->line_width))
        {
            Con_Linefeed(self, skip_notify);

        }

        txt++;

        switch (c)
        {
        case '\n':
            Con_Linefeed(self, skip_notify);
            break;
        case '\r':
            self->x = 0;
            break;
        default: // display character and advance
            y = self->current_line % self->total_lines;
            self->text[y * self->line_width + self->x] = (color << 8) | c;
            self->x++;
            if (self->x >= self->line_width)
            {
                Con_Linefeed(self, skip_notify);
                self->x = 0;
            }
            break;
        }
    }

    // mark time for transparent overlay
    if (self->current_line >= 0)
    {
        // NERVE - SMF
        if (skip_notify)
        {
            prev = self->current_line % NUM_CON_TIMES - 1;
            if (prev < 0)
                prev = NUM_CON_TIMES - 1;
            self->times[prev] = 0;
        }
        else
        {
            // -NERVE - SMF
            //self->times[self->current_line % NUM_CON_TIMES] = cls.realtime;
        }
    }
}







Game *Game_New(bool init)
{
    Game *game = malloc(sizeof(*game));

    if (!game)
    {
        return NULL;
    }

    if (init)
    {
        Game_Init(game);
    }

    return game;
}

void Game_ProcessInput(Game *self)
{
    SDL_Event e;
    // Handle events on queue
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            self->running = false;
        }
    }
}

void Game_Init(Game *self)
{
    self->running = true;
    self->update_counter = 0;
    self->screen = Screen_New(true);
}

void Game_Update(Game *self)
{
    Game_ProcessInput(self);
    Screen_Update(self->screen);
    self->update_counter++;
    printf("Called Game_Update The %d Time!\n", self->update_counter);
    
}

void Game_ShutDown(Game *self)
{
    Screen_Shutdown(self->screen);
    free(self);
    SDL_Quit();
}
