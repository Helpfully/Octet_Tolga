#include <string.h>


namespace octet
{
  enum 
  {
    BOX_TUMBLE_DEBUG_MODE = 0,
    BOX_TUMBLE_LAYOUT_SIZE = 30
  };
  struct game_layout
  {
    char row[BOX_TUMBLE_LAYOUT_SIZE + 1];
    game_layout *next;
  };
  
  class box_tumble_file_reader
  {
    FILE *file;
    game_layout *head;
    bool successful;

    void box_tumble_debug_printf(char *str)
    {
      if(BOX_TUMBLE_DEBUG_MODE)
      {
        printf(str);
      }
    }

    /*void init_head()
    {
      head = new game_layout();
      head->next = NULL;
      memset(head->row, ' ', sizeof(head->row));
    }*/

    void add_row()
    {
      game_layout *newRow;
      newRow = new game_layout();
      newRow->next = head;
      head = newRow;
      memset(newRow->row, ' ', sizeof(newRow->row));
      newRow->row[BOX_TUMBLE_LAYOUT_SIZE] = '\n';
    }

    void print_rows()
    {
      game_layout *ind = head;
      while(ind != NULL)
      {
        printf(ind->row);
        ind = ind->next;
      }
    }

    void finalize_read()
    {
      fclose(file);
    }

    public:

    int box_number;

    box_tumble_file_reader()
    {
      box_number = 0;
      file = fopen("../../assets/test.txt", "r");
      if(file == NULL)
      {
        box_tumble_debug_printf("Open file failed!!!");
        successful = false;
      }
      else
      {
        successful = true;
      }
      head = NULL;
    }

    game_layout *get_head()
    {
      return head;
    }

    game_layout *read_layout()
    {
      if(!successful)
      {
        return NULL;
      }
      else
      {
        char c = fgetc(file);
        bool needsFastForward, isFirst = true;
        add_row();
        while(c != EOF)
        {
          if(isFirst)
          {
            isFirst = false;
          }
          else
          {
            c = fgetc(file);
          }
          needsFastForward = true;
          for(int i = 0; i < BOX_TUMBLE_LAYOUT_SIZE; i++)
          {
            if(c == '\n')
            {
              add_row();
              needsFastForward = false;
              break;
            }
            if(c == EOF)
            {
              needsFastForward = false;
              break;
            }
            head->row[i] = c;
            if(c != ' ')
            {
              box_number++;
            }
            c = fgetc(file);
          }
          while(needsFastForward && c != EOF)
          {
            if(c == '\n')
            {
              add_row();
              break;
            }
            c = fgetc(file);
          }
        }

        print_rows();
        finalize_read();
        return head;
      }
    }
  };
}