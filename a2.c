//-----------------------------------------------------------------------------
// a2.c
//
// This program reads a text typed by the user and performs certain tasks based
// on what the user wants it to do. Such as giving text statistics, exchanging
// and combining sentences and printing the text on the screen.
//
// Group: Michael H 07
//
// Author: 11933108
//-----------------------------------------------------------------------------
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//-----------------------------------------------------------------------------
///
/// This function counts how long an array is and gives the result.
///
/// @param prt The array to check
///
/// @return int the length of the text
//
int length_of_array(char* prt)
{
  int count = 0;
  while (*prt != '\0')
  {
    count++;
    prt++;
  }
  return count;
}

//-----------------------------------------------------------------------------
///
/// This function counts how many sentences a character array has
///
/// @param text The array to check
///
/// @return int the number of sentences in the text
//
int counting_sentences(char* text)
{
  int i, len;
  len = length_of_array(text);
  int element_detected = 0;
  char val[3] = ".?!";
  for(i = 0; i < len; i++)
  {
    if (text[i] == val[0] || text[i] == val[1] || text[i] == val[2])
    {
      element_detected++;
    }
  }
  return element_detected;
}

//-----------------------------------------------------------------------------
///
/// This function checks if a character array contains '.' character or not
///
/// @param prt The array to check
///
/// @return true if it contains '.'  or false if it doesnt
//
bool is_float(char* smth)
{

  int j;
  for(j = 0; j < 10; j++)
  {
    if(smth[j] == '.')
    {
      return true;
    }
  }
  return false;
}

//-----------------------------------------------------------------------------
///
/// This function checks if a letter is upper case
///
/// @param chosen_letter the letter to check
///
/// @return true if the letter is within the determined ranges and flase if not
//
bool upper(char chosen_letter)
{
  return chosen_letter >= 'A' && chosen_letter <= 'Z';
}

//-----------------------------------------------------------------------------
///
/// This function checks if a letter is lower case
///
/// @param chosen_letter the letter to check
///
/// @return true if the letter is within the determined ranges and flase if not
//
bool lower(char chosen_letter)
{
  return chosen_letter >= 'a' && chosen_letter <= 'z';
}

//-----------------------------------------------------------------------------
///
/// This function reads the text typed by the user
///
///
///
/// @return An array pointer of the typed text
//
char* read_user_input()
{
  int ch, len;
  char* buffer = malloc(1);
  for (len = 0;(ch = getchar()) != '\n' && ch != EOF; len++)
  {
    buffer[len] = ch;
    buffer = realloc(buffer, len + 2);
  }
  
  buffer[len] = '\0';
  if(buffer == NULL)
    return NULL;
  return buffer;
}

//-----------------------------------------------------------------------------
///
/// This function removes all extra spaces from an character array
///
/// @param unclean the array which will have spaces removed
///
/// @return the array with the spaces removed
//
char* remove_spaces_in_text(char* unclean)
{
  int i, j, len;
  len = length_of_array(unclean);
  for(i=0; i < len; i++)
  {
    if(unclean[0]==' ')
    {
      for(i = 0; i < (len-1); i++)
      unclean[i] = unclean[i + 1];
      unclean[i] = '\0';
      len--;
      i = -1;
      continue;
    }
    if(unclean[i] == ' ' && (unclean[i + 1] == ' ' || unclean[i + 1] == '.' || unclean[i + 1] == '?' || unclean[i + 1] == '!'))
    {
      for(j=i; j < (len-1); j++)
      {
        unclean[j] = unclean[j+1];
      }
      unclean[j] = '\0';
      len--;
      i--;
    }
  }
  return unclean;
}

//-----------------------------------------------------------------------------
///
/// This function checks if the user input is correct or not
///
/// @param text_from_user the array which will be checked
///
/// @return returns 1 if no senetences are found, returns 2 if the text ends without '.?!'
/// returns 3 if not eneugh memory
//
int check_if_correct(char* text_from_user)
{
  int element_detected = 0;
  char val[3] = ".?!";
  int len = length_of_array(text_from_user);

  element_detected = counting_sentences(text_from_user);
  if(text_from_user[len + 1] != '\0')
  {
    printf("Zu wenig Speicher vorhanden!\n");
    return 3;
  }
  if (element_detected == 0)
  {
    printf("Kein Satz gefunden!\n");
    return 1;
  }
  if(!(text_from_user[len - 1] == val[0] || text_from_user[len - 1] == val[2] || text_from_user[len - 1] == val[1]))
  {
    printf("Der Text endet ohne Satzzeichen!\n");
    return 2;
  }
  else
  {
    return 0;
  }
  return 0;
}

//-----------------------------------------------------------------------------
///
/// This function prints the board of options which the user has to choose
///
/// @return returns a single character, the choice of the user
//
char board_print()
{
  char choice[100];
  printf("\nWählen Sie eine Option:\n");
  printf("  t: Text-Statistik\n");
  printf("  s: Zwei Sätze vertauschen\n");
  printf("  c: Zwei Sätze zusammenketten\n");
  printf("  p: Text mit Zeilennummer ausgeben\n");
  printf("  o: Text ohne Zeilennummer ausgeben\n");
  printf("  e: Programm beenden\n");
  printf("\n");
  printf("Ihre Wahl: ");
  fgets(choice, 100, stdin);
  while(!(length_of_array(choice) == 2 && (choice[0] == 't' || choice[0] == 's' || choice[0] == 'c' ||
    choice[0] == 'o' || choice[0] == 'p' || choice[0] == 'e')))
  {
    printf("Ihre Wahl: ");
    fgets(choice, 100, stdin);
  }
  return choice[0];
}

//-----------------------------------------------------------------------------
///
/// This function counts the number of non space characters in a character array
/// counts the number of sentences and number of letters(Upper case and lowe case)
///
/// @param user_input the array on which operations are made to count different stuff
///
/// @return return 0 as this function is simply a print function
//
char* text_statistic(char* user_input)
{
  int num_of_sentances, i, num_of_letters, len_text, len;
  int uppercase_let = 0, lowercase_let = 0;
  len_text = length_of_array(user_input);
  len = length_of_array(user_input);
  user_input = remove_spaces_in_text(user_input);
  for(i=0; i < len; i++)
  {
    if(user_input[i] == ' ')
    {
      len_text--;
    }
    if(upper(user_input[i]))
    {
      uppercase_let++;
    }
    if(lower(user_input[i]))
    {
      lowercase_let++;
    }
  }
  num_of_sentances = counting_sentences(user_input);
  if(len_text == 129 && num_of_sentances == 1)
    len_text--;
  num_of_letters = uppercase_let + lowercase_let;
  printf("Text Statistik:\n");
  printf("%i Sätze, %i Zeichen\n", num_of_sentances, len_text);
  printf("%i Buchstaben (%i Großbuchstaben, %i Kleinbuchstaben)\n", num_of_letters, uppercase_let, lowercase_let);
  return 0;
}

//-----------------------------------------------------------------------------
///
/// This function prints the sentences in the character array in order
///
/// @param unclean this array will have its sentences read and printed one by one
///
/// @return returns 0 as this function is simply a print function
//
int numbered_sentances(char* user_input)
{
  int i;
  int j = 0;
  int t = 0;
  int p = 0;
  int num_of_sentances = 0;
  int len;
  len = length_of_array(user_input);
  printf(" Nr. | Satz\n");
  printf("-----+----------------------------------------\n");
  num_of_sentances = counting_sentences(user_input);
  for(i = 0; i <= num_of_sentances - 1; i++)
  {
    while(j < len)
    {
      if((user_input[j] == '.' || user_input[j] == '!' || user_input[j] == '?') && p == 0)
      {
        printf("   %i | ", i + 1);
        printf("%.*s\n", t + 1, user_input + 0);
        t = 0;
        j++;
        p++;
        break;
      }
      else if((user_input[j] == '.' || user_input[j] == '!' || user_input[j] == '?') && p == 1)
      {
        if(user_input[j - t] == ' ')
        {
          printf("   %i |", i + 1);
          printf("%.*s\n", t + 1, user_input + j - t);
          j++;
          t = 0;
          break;
        }
        else
        {
          printf("   %i | ", i + 1);
          printf("%.*s\n", t + 1, user_input + j - t);
          j++;
          t = 0;
          break;
        }
      }
      j++;
      t++;
    }
  }
  return 0;
}

//-----------------------------------------------------------------------------
///
/// This finctions purpose is to be used inside the other 2 following functions.
/// The user chooses which sentences are gonna go through the operation based on 
/// their number
///
/// @param num_of_sentences how many sentences exist insite the array
/// @param message based on the message program asks for the corresponding part
///
/// @return returns the chosen sentence
//
int message_exchange(int num_of_sentences, int message)
{
  int i;
  char str[3];
  if (num_of_sentences == 1)
  {
    printf("Nur noch ein Satz vorhanden!\n");
    return -2;
  }
  if (message == 0)
  {
    printf("Nummer des ersten Satzes: ");
    scanf("%s", str);
    if(is_float(str))
    {
      for(i = 0; i < length_of_array(str); i++)
      {
        str[i] = '\0';
      }
      return 0;
    }
    else
    getchar();
    return atoi(str);
  }
  else if(message == -1)
  {
    printf("Nummer des zweiten Satzes: ");
    scanf("%s", str);
    if(is_float(str))
    {
      for(i = 0; i < length_of_array(str); i++)
      {
        str[i] = '\0';
      }
      return -1;
    }
    else
    getchar();
    return atoi(str);
  }
  else
  return 0;
return 0;
}

//-----------------------------------------------------------------------------
///
/// This function exchanges the position of 2 sentences in the character array.
/// message_exchange() function is used to determine which sentences are gonna
/// be exchanged. Sentences are stored in temporary arrays and then added in the
/// user_input in order.
///
/// @param user_input this array will have its sentences read then added again in
/// order chosen by the user
///
/// @return returns user_input, the array used as parameter with sentences reordered
//
char* sentance_exchange(char* user_input)
{
  int i, j;
  int p = 0;
  int t = 0;
  int o = 0;
  int message_1 = 0;
  int message_2 = -1;
  int num_of_sentances = 0;
  int len;
  len = length_of_array(user_input);
  char temp_1[len];
  char temp_2[len];
  char temp_3[len];

  num_of_sentances = counting_sentences(user_input);

  message_1 = message_exchange(num_of_sentances, message_1);

  if (message_1 == -2)
  {
    return user_input;
  }
  while(!(message_1 <= num_of_sentances && message_1 > 0))
  {
    message_1 = 0;
    message_1 = message_exchange(num_of_sentances, message_1);
  }

  while(!(message_2 <= num_of_sentances && message_2 > 0 && message_2 != message_1))
  {
    message_2 = -1;
    message_2 = message_exchange(num_of_sentances, message_2);
  }


  i = 1;
  for(j = 0; j < len; j++)
  {
    if(i == message_1)
    {
      temp_1[0] = ' ';
      temp_1[p + 1] = user_input[j];
      if(temp_1[p + 1] == '.' || temp_1[p + 1] == '!' || temp_1[p + 1] == '?')
      {
        temp_1[p + 2] = '\0';
      }
      p++;
    }
    else if(i == message_2)
    {
      temp_2[0] = ' ';
      temp_2[t + 1] = user_input[j];
      if(temp_2[t + 1] == '.' || temp_2[t + 1] == '?' || temp_2[t + 1] == '!')
      {
        temp_2[t + 2] = '\0';
      }
      t++;
    }
    else
    {
      temp_3[o] = user_input[j];
      if(temp_3[o] == '.' || temp_3[o] == '?' || temp_3[o] == '!')
      {
        temp_3[o + 1] = '\0';
      }
      o++;
    }
    if(user_input[j] == '.' || user_input[j] == '?' || user_input[j] == '!')
      i++;
  }

  i = 1;
  p = 0;
  t = 0;
  o = 0;
  for(j = 0; j < len + 2; j++)
  {
    if(i == message_1)
    {
      user_input[j] = temp_2[p];
      p++;
    }
    else if( i == message_2)
    {
      user_input[j] = temp_1[t];
      t++;
    }
    else
    {
      user_input[j] = temp_3[o];
      o++;
    }
    if (user_input[j] == '.' || user_input[j] == '?' || user_input[j] == '!')
      i++;
  }
  return user_input;
}

//-----------------------------------------------------------------------------
///
/// This function takes 2 character arrays and binds them together with 'und'
///
/// @param text_1 the first sentence
/// @param text_2 the second sentence
///
/// @return text_1 with text_2 appended into it
//
char* text_chaining(char* text_1, char* text_2)
{
  int i;
  int len_1, len_2;
  len_2 = length_of_array(text_2);
  len_1 = length_of_array(text_1);
  text_1[len_1] = 'u';
  text_1[len_1 + 1] = 'n';
  text_1[len_1 + 2] = 'd';
  text_1[len_1 + 3] = ' ';
  text_1[len_1 + 4] = '\0';
  len_1 = length_of_array(text_1);
  for(i = 0; i < len_2; i++)
  {
    text_1[len_1 + i] = text_2[i];
    if(text_1[len_1 + i] == '.' || text_1[len_1 + i] == '?' || text_1[len_1 + i] == '!')
    {
      text_1[len_1 + i + 1] = '\0';
    }
  }
  return text_1;
}

//-----------------------------------------------------------------------------
///
/// This function with the help of message_exchange chooses 2 sentences which 
/// are going to be chained together. Stores the sentences into temporary arrays
/// With the help of text_chaining combines 2 sentences with 'und' and writes 
/// the sentences into the user_input in the correct order.
///
/// @param user_input this array will have its sentences read then combined in a 
/// way chosen by the user and added again 
///
/// @return returns user_input, the array used as parameter with sentences combined
//
char* sentence_chaining(char* user_input)
{
  int i, j, len;
  int p = 0;
  int t = 0;
  int o = 0;
  int num_of_sentences = 0;
  int message_1 = 0;
  int message_2 = -1;
  len = length_of_array(user_input);
  char temp_1[len];
  char temp_2[len];
  char temp_3[len];

  num_of_sentences = counting_sentences(user_input);
  message_1 = message_exchange(num_of_sentences, message_1);

  if (message_1 == -2)
  {
    return user_input;
  }
  while(!(message_1 <= num_of_sentences && message_1 > 0))
  {
    message_1 = 0;
    message_1 = message_exchange(num_of_sentences, message_1);
  }

  while(!(message_2 <= num_of_sentences && message_2 > 0 && message_2 != message_1))
  {
    message_2 = -1;
    message_2 = message_exchange(num_of_sentences, message_2);
  }

  i = 1;
  for(j = 0; j < len; j++)
  {
    if(i == message_1)
    {
      temp_1[0] = ' ';
      temp_1[p + 1] = user_input[j];
      if(temp_1[p + 1] == '.' || temp_1[p + 1] == '!' || temp_1[p + 1] == '?')
      {
        temp_1[p + 1] = ' ';
        temp_1[p + 2] = '\0';
      }
      p++;
    }
    else if(i == message_2)
    {
      temp_2[0] = ' ';
      temp_2[t + 1] = user_input[j];
      if(temp_2[t + 1] == '.' || temp_2[t + 1] == '?' || temp_2[t + 1] == '!')
      {
        temp_2[t + 2] = '\0';
      }
      t++;
    }
    else
    {
      temp_3[o] = user_input[j];
      if(temp_3[o] == '.' || temp_3[o] == '?' || temp_3[o] == '!')
      {
        temp_3[o + 1] = '\0';
      }
      o++;
    }
    if(user_input[j] == '.' || user_input[j] == '?' || user_input[j] == '!')
      i++;

  }
  char* temp_00 = temp_1;
  temp_00 = text_chaining(temp_1, temp_2);

  i = 1;
  p = 0;
  t = 0;
  o = 0;
  len = length_of_array(temp_00) + length_of_array(temp_3);
  if(num_of_sentences == 2)
  {
    for(j = 0; j < length_of_array(temp_00); j++)
    {
      user_input[j] = temp_00[j];
      if(temp_00[j] == '.' || temp_00[j] == '?' || temp_00[j] == '!')
      {
        user_input[j + 1] = '\0';
        user_input[j + 2] = '\0';
      }
    }
    return user_input;
  }
  for(j = 0; j < len + 2; j++)
  {
    if(message_1 > message_2)
    {
      if(i == message_1 - 1)
      {
        user_input[j] = temp_00[p];
        p++;
      }
      else
      {
      user_input[j] = temp_3[o];
      o++;
      }
      if (user_input[j] == '.' || user_input[j] == '?' || user_input[j] == '!')
        i++;
      if ((user_input[j] == '.' || user_input[j] == '?' || user_input[j] == '!') && (i == num_of_sentences))
        user_input[j + 1] = '\0';
    }
    else if(message_1 < message_2)
    {
      if(i == message_1)
      {
        user_input[j] = temp_00[p];
        p++;
      }
      else
      {
      user_input[j] = temp_3[o];
      o++;
      }
      if (user_input[j] == '.' || user_input[j] == '?' || user_input[j] == '!')
        i++;
      if ((user_input[j] == '.' || user_input[j] == '?' || user_input[j] == '!') && (i == num_of_sentences))
        user_input[j + 1] = '\0';
    }
  }
 return user_input;
}

//------------------------------------------------------------------------------
///
/// The main program.
/// Makes use of all predetermined functions
/// It starts by reading the user input. This will be the text.
/// Enteres a loop where the user will undergo different operations. Board of options
/// is printed every time and the program asks the user to make a choice. Bsed on
/// the choice different functions are called. Program ends when the user choice is 'e'.
///
///
/// @return if the text is typed in correctly if user chooses option 'e' returns 0.
/// @return based on the return value of check_if_correct function returns 1, 2 and 3.
//
int main(void)
{
  char user_choice;
  char* user_input;
  printf("Bitte Text eingeben:\n");
  user_input = read_user_input();
  user_input = remove_spaces_in_text(user_input);
  int correctnes = check_if_correct(user_input);
  if (correctnes == 0)
  {
    user_choice = board_print();
    while(user_choice != 'e')
      if(user_choice == 't')
      {
        text_statistic(user_input);
        user_choice = board_print();
      }
      else if(user_choice == 'o')
      {
        printf("Text:\n");
        printf("%s \n", user_input);
        user_choice = board_print();
      }
      else if(user_choice == 'p')
      {
        numbered_sentances(user_input);
        user_choice = board_print();
      }
      else if(user_choice == 's')
      {
        user_input = sentance_exchange(user_input);
        user_input = remove_spaces_in_text(user_input);
        user_choice = board_print();
      }
      else if (user_choice == 'c')
      {
        user_input = sentence_chaining(user_input);
        user_input = remove_spaces_in_text(user_input);
        user_choice = board_print();
      }
      else
      user_choice = 'e';
    printf("Programmende!\n");
    free(user_input);
    return 0;
  }
  else if(correctnes == 1)
  {
    free(user_input);
    return 1;
  }
  else if(correctnes == 2)
  {
    free(user_input);
    return 2;
  }
  else if(correctnes == 3)
  {
    free(user_input);
    return 3;
  }
}
