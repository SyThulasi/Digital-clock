#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


// Functions prototype
void timerunning();
void hideCurcur();
void set_text_colour(int color);
void colour_print(int colour);
void printdate(int color_number, char *date_);
int input_colour(char *input);
void print_digit(char input,int position,int colour);
void colon(int position, int colour);
void print(int (*digit_)[6], int position, int colour);

int color_number;


int main(int argc, char **argv)
{

    // ----------------------- Argument error handling start -------------------------------
    // If the user doesn't mention the color. output the basic color (Black and white)
    if (argc == 1)
    {
        color_number = 7;
    }

    // If the user gives 2 argument
    if(argc == 2){

        if(strcmp(argv[1],"-h")==0)
            {
                printf("usage : clock -h                quick help on cmd\nusage : clock -c <color>        print clock with a color\n<color-black|red|green|yellow|blue|magenta|cyan|white>  supported colors\n");
                return 0;
            }
        else if (strcmp(argv[1],"-c")==0)
        {
            printf("Invalid use of arguments.\nusage : clock -h                quick help on cmd\nusage : clock -c <color>        print clock with a color\n");
            return 0;
        }
        else if (argv[1][0] != '-'){
            color_number = 7;
        }
        else
            {
            printf("Invalid use of arguments.\nusage : clock -h                quick help on cmd\nusage : clock -c <color>        print clock with a color\n");
            return 0;   
            }
    }

    // If the user gives more than three arguments
    else if ( argc >= 3 )
    {
        for (int i = 0; i < argc ; i++)
        {
            if (strcmp(argv[i],"-h")==0)
            {
                printf("usage : clock -h                quick help on cmd\nusage : clock -c <color>        print clock with a color\n<color-black|red|green|yellow|blue|magenta|cyan|white>  supported colors\n");
                return 0;
            }
            else if (strcmp(argv[i],"-c")==0){
                if(argv[i+1] != 0){

                    // Change the color name into the lower case if the user input as upper case letters
                    for (int m = 0; argv[i+1][m] != '\0'; m++) {
                        if(1>0){
                            if(argv[i+1][m] >= 'A' && argv[i+1][m] <= 'Z') {
                                argv[i+1][m] = argv[i+1][m] + 32;
                            }
                        }
                    }
                    
                    char *colour=(argv[i+1]);
                    color_number = input_colour(colour);
                    if (color_number >= 0 && color_number < 8)
                    {
                        color_number = color_number;
                        break;
                    }
                    else if (color_number == 366){
                        printf("%s :This is not a valid color, Please enter one of these colours: black, red, green, yellow, blue, magenta, cyan, white\n", argv[i+1] );
                        return 0;
                    }
                }
                else{
                    printf("Invalid use of arguments.\nusage : clock -h                quick help on cmd\nusage : clock -c <color>        print clock with a color\n");
                    return 0;   
                }
            }
            else if (argv[i][0] != '-')
            {
                color_number = 7;
            }
            
            else{
                printf("Invalid use of arguments.\nusage : clock -h                quick help on cmd\nusage : clock -c <color>        print clock with a color\n");
                return 0;
            }
            
        }
        
    }
    
    // ----------------------- Argument error handling end -------------------------------


    // Function for hide the cursur and clear the terminals
    hideCurcur();

    // Function for run the system Time
    timerunning();
    
    // Reset the background colour to normal
	printf("\033[0m");

    return 0;
}



// Function for run time
void timerunning(){
    for(;;){				// For endless loop
		char time_digit[20], date[20];
        time_t rawtime;                     // time_t used to store system time values
        struct tm *timeparts;               // Converts time into parts like hours, min, sec
        time(&rawtime);
        timeparts = localtime(&rawtime);

        strftime(date,20,"%Y-%m-%d  ", timeparts);	// Date
  		strftime(time_digit,20,"%X", timeparts);	// Current time

        // Print time
        for(int digit_position = 0; digit_position < 8; digit_position++){

            // print 1st colon
            if (digit_position == 2){
                colon(digit_position, color_number);
            }

            // print second colon
            else if (digit_position == 5)
            {
                colon(digit_position, color_number);
            }
            // call function for print the time
            else{
                print_digit(time_digit[digit_position], digit_position, color_number);
            }
        }
        printf("\033[0m");

        // print date 
        printdate(color_number, date);
       sleep(0.75);
    }
}

//----------------function for print date-----------------------------------------
void printdate(int color_number, char *date_){
    	printf("\033[8;23H");					// for print the date in the center

		// assign colour for the date
        set_text_colour(color_number);

		// Print the date using for loop
		for(int i = 0 ; i < 12 ; i++){
  		    printf("%c",date_[i]);
  		}

		printf("\033[0m");
		putchar('\n');
}

//----------------Function for hide the cursur------------------------------------
void hideCurcur(){
    printf("\033[?25l");	// Hiding the cursor
	printf("\033[2J");		// Clear console
}

//----------------Add colour for the text----------------------------------------------
void set_text_colour(int color){
    printf("\033[%dm", (color + 30));
}


//--------------Function for assign the numbers for the colors-------------------------
int input_colour(char *input){

	char *colours[]={"black","red","green","yellow","blue","magenta","cyan","white"};

	// Check what color was entered by the user
	for(int col_no = 0; col_no < 8; col_no++){

        if(1>0){
            if(strcmp(input, colours[col_no]) == 0){
                return col_no;
            }
        }
 	}
	//If the color entered by the user is not in our color list  return 366
    // Don't panic 366 is my e number, just return for 
 	return 366;
}


//---------------Function  fot Define the colon by using array and print it.----------------------
void colon(int position, int colour){

    // set the curcur position for colons
    int x_position;
    if(position == 2){
        x_position = 16;
    }
    else if(position == 5){
        x_position = 35;
    }


	// define pixel using  2D array for colon
	int array[5][4]={
		{0,0,0,0},
        {0,1,1,0},
        {0,0,0,0},
        {0,1,1,0},
        {0,0,0,0}
	};

	// Print the colon as same as print the digits above
	for(int row = 0; row <=5; row++){

		for(int column = 0; column <= 4;column ++){

            // assign cursur to the correct position
			printf("\033[%d;%dH",(row+2), (column + x_position));

			if(array[row][column] == 0){

				printf("\033[0m");
				printf(" ");
			}

			else if(array[row][column] == 1){

				printf("\033[%dm", (colour + 40));
				printf(" ");
			}
		}
	printf("\033[0m");
	putchar('\n');
	}

}


//----------------Defining and print each digit------------------------------------
void print_digit(char input, int position, int colour){
	int digit;

    // conver the digit number from char to integer
    char digits[] = {'0','1','2','3','4','5','6','7','8','9'};

	for(int number = 0; number < 10; number++){

 		if(input == digits[number]){
 			digit = number;
 		}
 	}

	// Define digits using a 2D(5 x 6) array
    switch (digit){
        case 0:
            {
                int digitpixels[5][6] = {
                    {1, 1, 1, 1, 1, 1},
                    {1, 1, 0, 0, 1, 1},
                    {1, 1, 0, 0, 1, 1},
                    {1, 1, 0, 0, 1, 1},
                    {1, 1, 1, 1, 1, 1}};

                print(digitpixels, position, colour);
                break;

            }
        case 1:
            {
                int digitpixels[5][6] = {
                    {0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 1, 1}};

                print(digitpixels, position, colour);

                break;

            }
        case 2:
            {
                int digitpixels[5][6] = {
                    {1, 1, 1, 1, 1, 1},
                    {0, 0, 0, 0, 1, 1},
                    {1, 1, 1, 1, 1, 1},
                    {1, 1, 0, 0, 0, 0},
                    {1, 1, 1, 1, 1, 1} };

                print(digitpixels, position, colour);

                break;

            }
        case 3:
            {
                int digitpixels[5][6] = {
                    {1, 1, 1, 1, 1, 1},
                    {0, 0, 0, 0, 1, 1},
                    {1, 1, 1, 1, 1, 1},
                    {0, 0, 0, 0, 1, 1},
                    {1, 1, 1, 1, 1, 1}};

                print(digitpixels, position, colour);

                break;

            }
        case 4:
        {
            int digitpixels[5][6] = {
                {1, 1, 0, 0, 1, 1},
                {1, 1, 0, 0, 1, 1},
                {1, 1, 1, 1, 1, 1},
                {0, 0, 0, 0, 1, 1},
                {0, 0, 0, 0, 1, 1}};

                print(digitpixels, position, colour);

                break;

        }
        case 5:
        {
            int digitpixels[5][6] = {
                {1, 1, 1, 1, 1, 1},
                {1, 1, 0, 0, 0, 0},
                {1, 1, 1, 1, 1, 1},
                {0, 0, 0, 0, 1, 1},
                {1, 1, 1, 1, 1, 1}};

                print(digitpixels, position, colour);

                break;

        }
        case 6:
        {
            int digitpixels[5][6] = {
                {1, 1, 1, 1, 1, 1},
                {1, 1, 0, 0, 0, 0},
                {1, 1, 1, 1, 1, 1},
                {1, 1, 0, 0, 1, 1},
                {1, 1, 1, 1, 1, 1}};

                print(digitpixels, position, colour);

                break;

        }
        case 7:
        {
            int digitpixels[5][6] = {
                {1, 1, 1, 1, 1, 1},
                {0, 0, 0, 0, 1, 1},
                {0, 0, 0, 0, 1, 1},
                {0, 0, 0, 0, 1, 1},
                {0, 0, 0, 0, 1, 1}};

                print(digitpixels, position, colour);

                break;

        }
        case 8:
        {
            int digitpixels[5][6] = {
                {1, 1, 1, 1, 1, 1},
                {1, 1, 0, 0, 1, 1},
                {1, 1, 1, 1, 1, 1},
                {1, 1, 0, 0, 1, 1},
                {1, 1, 1, 1, 1, 1}};

                print(digitpixels, position, colour);

                break;

        }
        case 9:
        {
            int digitpixels[5][6] = {
                {1, 1, 1, 1, 1, 1},
                {1, 1, 0, 0, 1, 1},
                {1, 1, 1, 1, 1, 1},
                {0, 0, 0, 0, 1, 1},
                {1, 1, 1, 1, 1, 1}};

                print(digitpixels, position, colour);

                break;

        }
    }
}

//--------------Function for print digits----------------------------------------------------------
void print(int (*digit_)[6], int position, int colour){

    for(int row = 0 ;row < 5; row++){

		for(int column = 0 ;column < 6 ; column++){

            // set spacing for the digits
            int spacing;
            if (position == 0){spacing=2;}
            else if(position == 1){spacing=9;}
            else if(position == 3){spacing=21;}
            else if(position == 4){spacing=28;}
            else if(position == 6){spacing=40;}
            else if(position == 7){spacing=47;}
             // set spacing for the digits

			printf("\033[%d;%dH", row+2 , column + spacing);	// assign the position for the digit

            //assign print value
			int value = digit_[row][column];

			// In the 2D array value is 0 print the colourless space( )
			if(value == 0){
				printf("\033[0m");
				printf(" ");
			}

			// In the 2D array value  is 1 print the colour space( )
			else if(value == 1){
				//printf("\033[%dm", (colour+40));
                colour_print(colour);
				printf(" ");
			}
		}
        printf("\033[0m"); // Reset the colour to colourless
		putchar('\n');
	}
}

//-----------------functio for set the colours for background------------------------------------------
void colour_print(int colour){
    printf("\033[%dm", (colour+40));
}