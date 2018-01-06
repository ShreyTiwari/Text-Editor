#include <stdio.h>
#include <stdlib.h>

#define OP_INSERT_CHAR 		'I' //Insert
#define OP_PRESSED_ENTER 	'N' //Newline
#define OP_PRESSED_DELETE 	'D' //Delete 
#define OP_PRESSED_LEFT 	'h' //Left arrow equivalent in vi editor
#define OP_PRESSED_DOWN 	'j' //Down arrow equivalent in vi editor
#define OP_PRESSED_UP 		'k' //Up arrow equivalent in vi editor
#define OP_PRESSED_RIGHT 	'l' //Right arrow equivalent in vi editor
#define OP_PRESSED_HOME 	'H' //Home
#define OP_PRESSED_END 		'E' //End
#define OP_PRINT_LINE 		'P' //Print the current line
#define OP_PRINT_TEXT 		'T' //print the whole Text
#define OP_QUIT 		'Q' //Quit the editor

//Forward declaration; see the definition of struct for more details.
struct text_node;

//A node in 
struct line_node {
	char ch;
	struct line_node *next_char;
	struct line_node *prev_char;
	struct text_node *line_header;
};

struct text_node {
	struct line_node *line_begin;
	struct text_node *next_line;
	struct text_node *prev_line;
};

//Creates the empty text. 
//Empty text has one empty line, which has a newline '\n' as end of line.
struct text_node *create_text(struct line_node **pcursor);

//Free the whole text
void free_text(struct text_node *text);

//Insert a char just before the cursor. 
//Cursor always points to a line_node. 
//A line has a newline char as the end of line.
struct line_node *op_insert_char(struct line_node *cursor, char ch);

//“Enter” (i.e. create) a new line and the cursor moves to the new line. 
//If the cursor was at the end of line, a new empty line is created, otherwise 
//the current line is split into a new line starting from the character at the cursor.
struct line_node *op_pressed_enter(struct line_node *cursor);

//“Delete” a character at the cursor, or the end of line if the cursor is 
//at the end of a line. Deleting an end of line is essentially concatenating 
//the next line with the current line. 
//No operation if the cursor is at the end of line of the last line.
struct line_node *op_pressed_delete(struct line_node *cursor);

//Move the cursor “Left” by a character (or to the end of line of 
//above line if the cursor is at the beginning of a line). 
//No operation if the cursor is the beginning of the first line.
struct line_node *op_pressed_left(struct line_node *cursor);

//Move the cursor “Down” to the below line (beginning of the below line). 
//No operation if the cursor is already at the last line.
struct line_node *op_pressed_down(struct line_node *cursor);

//Move the cursor “Up” to the above line (beginning of the above line). 
//No operation if the cursor is already at the first line.
struct line_node *op_pressed_up(struct line_node *cursor);

//Move the cursor “Right” by a character (or to the beginning of below line 
//if the cursor is at the end of a line). 
//No operation if the cursor is the end of line of the last line.
struct line_node *op_pressed_right(struct line_node *cursor);

//Move the cursor to “Home”, that is, beginning of the current line. 
//No operation if the cursor is at the beginning of a line.
struct line_node *op_pressed_home(struct line_node *cursor);

//Move the cursor to “End”, that is, end of line the current line. 
//No operation if the cursor is at the end of a line.
struct line_node *op_pressed_end(struct line_node *cursor);

//“Print Line” prints the current line.
void op_print_line(struct line_node *cursor);

//“Print Text” prints the whole text.
void op_print_text(struct text_node *text);

int main() {
	struct line_node *cursor;
	struct text_node *text = create_text(&cursor);
	char op[4];

	do {
	    op[2] = ' ';
		scanf(" %[^\n]", op);
		switch(op[0]) {
	        case OP_INSERT_CHAR:
	            cursor = op_insert_char(cursor, op[2]);
	            break;
	        case OP_PRESSED_ENTER:
	            cursor = op_pressed_enter(cursor);
	            break;
	        case OP_PRESSED_DELETE:
	            cursor = op_pressed_delete(cursor);
	            break;
	        case OP_PRESSED_LEFT:
	            cursor = op_pressed_left(cursor);
	            break;
	        case OP_PRESSED_DOWN:
	            cursor = op_pressed_down(cursor);
	            break;
	        case OP_PRESSED_UP:
	            cursor = op_pressed_up(cursor);
	            break;
	        case OP_PRESSED_RIGHT:
	            cursor = op_pressed_right(cursor);
	            break;
	        case OP_PRESSED_HOME:
	            cursor = op_pressed_home(cursor);
	            break;
	        case OP_PRESSED_END:
	            cursor = op_pressed_end(cursor);
	            break;
	        case OP_PRINT_LINE:
	            op_print_line(cursor);
	            break;
	        case OP_PRINT_TEXT:
	            op_print_text(text);
	            break;	        
	    }
	} while(op[0] != OP_QUIT);
	
	free_text(text);
	return 0;
}

struct text_node *create_text(struct line_node **pcursor)
{
	*pcursor = (struct line_node*)malloc(sizeof(struct line_node));
	(*pcursor)->ch = '\n';
	(*pcursor)->next_char = (*pcursor)->prev_char = NULL;

	struct text_node *temp = (struct text_node*)malloc(sizeof(struct text_node));
	temp->next_line = temp->prev_line = NULL;
	temp->line_begin = *pcursor;

	(*pcursor)->line_header = temp;

	return temp;
}

void free_text(struct text_node *text)
{
	struct text_node *y, *temp = text;
	struct line_node *x, *next;
	while(temp != NULL)
	{
		x = temp->line_begin;
		while(x!=NULL)
		{
			next = x->next_char;
			free(x);
			x = next;
		}
		y = temp->next_line;
		free(temp);
		temp = y; 
	}
}


void op_print_line(struct line_node *cursor)
{
	struct line_node *temp = cursor->line_header->line_begin;

	while(temp != NULL)
	{
		printf("%c", temp->ch);
		temp = temp->next_char;
	}
}

void op_print_text(struct text_node *text)
{
	struct text_node *temp = text;
	struct line_node *x;
	while(temp != NULL)
	{
		x = temp->line_begin;
		while(x != NULL)
		{
			printf("%c", x->ch);
			x = x->next_char;
		}
		temp = temp->next_line;
	}
}

struct line_node *op_pressed_home(struct line_node *cursor)
{
	struct line_node *temp = cursor->line_header->line_begin;
	return temp;
}

struct line_node *op_pressed_end(struct line_node *cursor)
{
	struct line_node *temp = cursor;
	while(temp->ch != '\n')
	{
		temp = temp->next_char;
	}
	return temp;
}

struct line_node *op_pressed_up(struct line_node *cursor)
{
	struct text_node *temp = cursor->line_header->prev_line;
	if(temp == NULL)
		return cursor;
	else
		return temp->line_begin;
}

struct line_node *op_pressed_down(struct line_node *cursor)
{
	struct text_node *temp = cursor->line_header->next_line;
	
	if(temp == NULL)
		return cursor;
	else
		return temp->line_begin;
}

struct line_node *op_pressed_left(struct line_node *cursor)
{
	struct line_node *temp = cursor;
	if(cursor->prev_char == NULL)
	{
		struct text_node *x = cursor->line_header;
		x = x->prev_line;
		if(x == NULL)
			return cursor;
		else
			return(op_pressed_end(x->line_begin));
	}
	else
		return cursor->prev_char;	
}

struct line_node *op_pressed_right(struct line_node *cursor)
{
	struct line_node *temp = cursor;
	if(cursor->next_char == NULL)
	{
		struct text_node *x = cursor->line_header->next_line;

		if(x == NULL)
			return cursor;
		else
		 return x->line_begin;
	}
	else
	{
		return cursor->next_char;
	}
}

struct line_node *op_pressed_enter(struct line_node *cursor)
{
	if(cursor->ch == '\n')
	{
		struct text_node *currLine = cursor->line_header,*temp = (struct text_node*)malloc(sizeof(struct text_node));
		temp->prev_line = currLine;
		if(currLine->next_line == NULL)
		{
			currLine->next_line = temp;
			temp->next_line = NULL;
		}
		else
		{
			currLine->next_line->prev_line = temp;
			temp->next_line = currLine->next_line;
			currLine->next_line = temp;
		}

		struct line_node *x = (struct line_node*)malloc(sizeof(struct line_node));
		x->ch = '\n';
		x->next_char = x->prev_char = NULL;
		x->line_header = temp;

		temp->line_begin = x;

		cursor = x;
	}
	else
	{
		struct text_node *temp = (struct text_node*)malloc(sizeof(struct text_node));
		
		if(cursor->prev_char != NULL)
		{
			struct line_node *x = (struct line_node*)malloc(sizeof(struct line_node));
			x->ch = '\n';
			x->next_char = NULL;
			x->prev_char = cursor->prev_char;
			cursor->prev_char->next_char = x;

			temp->line_begin = cursor;
			cursor->prev_char = NULL;

			struct line_node *p = cursor;
			while(p!=NULL)
			{
				p->line_header = temp;
				p = p->next_char;
			}
			
			if(x->line_header->next_line == NULL)
			{
				x->line_header->next_line = temp;
				temp->prev_line = x->line_header;
				temp->next_line = NULL;
			}
			else
			{
				x->line_header->next_line->prev_line = temp;
				temp->next_line = x->line_header->next_line;
				temp->prev_line = x->line_header;
				x->line_header->next_line = temp;
			}
		}

		else
		{
			struct text_node *temp = (struct text_node*)malloc(sizeof(struct text_node));
			
			struct line_node *x =  (struct line_node*)malloc(sizeof(struct line_node));
			x->ch = '\n';
			x->next_char = x->prev_char = NULL; 
			x->line_header = temp;

			temp->next_line = cursor->line_header;
			if(cursor->line_header->prev_line != NULL)
			{
				temp->prev_line = cursor->line_header->prev_line;
				cursor->line_header->prev_line->next_line = temp;
				cursor->line_header->prev_line = temp;

			}
			else
			{
				cursor->line_header->prev_line = temp;
				temp->next_line = cursor->line_header;
			}
							
			temp->line_begin = x;
		}
	}
	return cursor;
}

struct line_node *op_insert_char(struct line_node *cursor, char ch)
{
	struct line_node *temp = (struct line_node*)malloc(sizeof(struct line_node));
	temp->ch = ch;
	temp->line_header = cursor->line_header;

	if(cursor->prev_char == NULL)
	{
		cursor->prev_char = temp;
		temp->next_char = cursor;
		temp->prev_char = NULL;
		cursor->line_header->line_begin = temp;
		return cursor;
	}
	else
	{
		temp->next_char = cursor;
		cursor->prev_char->next_char = temp;
		temp->prev_char = cursor->prev_char;
		cursor->prev_char = temp;
		return cursor;
	}
}

struct line_node* op_pressed_delete(struct line_node* cursor)
{
    if(cursor->next_char==NULL)
    {
        if(cursor->line_header->next_line==NULL)
             return cursor;
    }
    
    else if(cursor->next_char==NULL && cursor->line_header->next_line!=NULL)
    {
        if(cursor->prev_char!=NULL)
        {
            struct line_node *temp=cursor;
            struct line_node *x=cursor->line_header->next_line->line_begin;
            cursor->prev_char->next_char=cursor->line_header->next_line->line_begin;
            cursor->line_header->next_line->line_begin->prev_char=cursor->prev_char;
            if(cursor->line_header->next_line->next_line!=NULL)
            {
                cursor->line_header->next_line->next_line->prev_line=cursor->line_header;
            }
            cursor->line_header->next_line=cursor->line_header->next_line->next_line;
            while(x!=NULL)
            {
                x->line_header=cursor->line_header;
                x=x->next_char;
            }
            return(cursor->prev_char->next_char);
        }
        else
        {
            struct line_node *t=cursor;
            struct line_node *t1=cursor->line_header->next_line->line_begin;
            cursor->line_header->line_begin=t1;
            cursor->line_header->next_line=cursor->line_header->next_line->next_line;
            if(cursor->line_header->next_line!=NULL)
            {
                cursor->line_header->next_line->prev_line=cursor->line_header;
            }
            while(t1!=NULL)
            {
                t1->line_header=cursor->line_header;
                t1=t1->next_char;
            }
            cursor=cursor->line_header->line_begin;
        }        
    }
    else
    if(cursor->next_char!=NULL)
    {
        struct line_node *temp=cursor;
        if(cursor->prev_char!=NULL)
            cursor->prev_char->next_char=cursor->next_char;
        else
            cursor->line_header->line_begin=cursor->next_char;
        cursor->next_char->prev_char=cursor->prev_char;
        cursor=cursor->next_char;
        free(temp);
    }
    return cursor;
}

