#include "Matrix.h"



extern const char Number[10][5][3] PROGMEM;


extern const Alphabet_node Alphabet_table[27] PROGMEM;





// the lowest score is 0 and the highest score is 5.0.
void MATRIX::testMethod1()
{
	for (int i = 0; i <= 64; i++)
	{
		setStack(i);
	}
}


//Display the score using the first method.
//double Score  is the average score given by the students
void MATRIX::setStack(int number)
{
	if (0 <= number && number <= 64)
	{
		int Rows = number / Number_of_Rows;
		int Cols = number % Number_of_Cols;

		//The LEDs of these rows are all light.
		//For example: if the number is 35. than integer rows=35/8=4. So, the first 4 rows are light.
		digitalWrite(LATCH, LOW);
		shiftOut(SER_ROW, CLK_ROW, MSBFIRST, B11111111 << Rows);
		shiftOut(SER_COL, CLK_COL, MSBFIRST, B11111111);
		digitalWrite(LATCH, HIGH);

		digitalWrite(LATCH, LOW);
		shiftOut(SER_ROW, CLK_ROW, MSBFIRST, ~(B00000001 << Rows));
		shiftOut(SER_COL, CLK_COL, MSBFIRST, ~(B11111111 << Cols));
		digitalWrite(LATCH, HIGH);

	}
	else
	{
		Serial.println("Invalid score!!!");
	}
}

void MATRIX::testMethod2()
{
	for (int i = floor(Min_Score); i <= floor(Max_Score * 10); i++)
	{
		setDouble(i / 10.0);
	}
}



//Display the score using the second method.
//double Score : the average score given by the students
void MATRIX::setDouble(double number)
{
	//If we want to display 2.7, we need to split the 2 numbers
	int mid = floor(number * 10);    //2.7*10=27
	int First_Number = mid / 10;    //First_Number=2
	int Second_Number = mid % 10;   //Second_Number=7

	for (int i = 0; i < Time_Delay; i++)
	{
		lightFirstNumber(Number[First_Number]);
		lightSecondNumber(Number[Second_Number]);
	}
}


void MATRIX::lightFirstNumber(const char Number[5][3])
{
	for (int Col = 1; Col < 4; Col++) // the cols of the 1st number are col1, col2, col3
	{
		digitalWrite(LATCH, LOW);
		shiftOut(SER_COL, CLK_COL, MSBFIRST, 1 << (Col - 1));

		int row_data = 0;
		for (int Row = 1; Row < 6; Row++)
		{
			row_data = (row_data << 1) + pgm_read_byte_near(&Number[Row - 1][Col - 1]);
		}
		row_data <<= 3;
		shiftOut(SER_ROW, CLK_ROW, LSBFIRST, ~row_data);
		digitalWrite(LATCH, HIGH);
	}

	digitalWrite(LATCH, LOW);
	shiftOut(SER_COL, CLK_COL, MSBFIRST, B00001000);
	shiftOut(SER_ROW, CLK_ROW, MSBFIRST, B11101111);
	digitalWrite(LATCH, HIGH);

}

void MATRIX::lightSecondNumber(const char Number[5][3])
{
	for (int Col = 5; Col < 8; Col++) // the cols of the 1st number are col1, col2, col3
	{
		digitalWrite(LATCH, LOW);
		shiftOut(SER_COL, CLK_COL, MSBFIRST, 1 << (Col - 1));

		int row_data = 0;
		for (int Row = 1; Row < 6; Row++)
		{
			row_data = (row_data << 1) + pgm_read_byte_near(&Number[Row - 1][Col - 5]);
		}
		row_data <<= 3;
		shiftOut(SER_ROW, CLK_ROW, LSBFIRST, ~row_data);
		digitalWrite(LATCH, HIGH);
	}

}

void MATRIX::setInteger(int number)
{

	for (int Col = 1; Col < 4; Col++) // the cols of the 1st number are col1, col2, col3
	{
		digitalWrite(LATCH, LOW);
		shiftOut(SER_COL, CLK_COL, MSBFIRST, 1 << (Col - 1));

		int row_data = 0;
		for (int Row = 1; Row < 6; Row++)
		{
			row_data = (row_data << 1) + pgm_read_byte_near(&Number[number][Row - 1][Col - 1]);
		}
		row_data <<= 3;
		shiftOut(SER_ROW, CLK_ROW, LSBFIRST, ~row_data);
		digitalWrite(LATCH, HIGH);
	}
}

void MATRIX::testMethod3()
{
	for (int i = Min_Score; i <= Max_Score; i++)
	{
		setLevel(0.1 + i, 5);
	}
}

//Display the score using the second method.
//double Score : the average score given by the students

void MATRIX::setLevel(double level, int speed)
{
	if (Min_Score <= level && level <= Max_Score)
	{
		String words;
		if (level >= Boundary_of_Very_Good * Max_Score)
		{
			words = Level5;
		}
		else
		{
			if (level >= Boundary_of_Good * Max_Score)
			{
				words = Level4;
			}
			else
			{
				if (level >= Boundary_of_Normal * Max_Score)
				{
					words = Level3;
				}
				else
				{
					if (level >= Boundary_of_Bad * Max_Score)
					{
						words = Level2;
					}
					else
					{
						words = Level1;
					}
				}
			}
		}

		//modify the code and you can display any words.
		//words="any words"
		char words_buffer[8][8 * 100];
		words.toUpperCase();

		//use the alphabet unit to make a sentence and storage the sentence into words_buffer
		for (int i = 0; i < words.length(); i++)
		{
			char current_alphabet = words.charAt(i);
			int alphabet_index = getIndex(current_alphabet);
			for (int row = 0; row < Number_of_Rows; row++)
			{
				for (int col = 0; col < Number_of_Cols; col++)
				{
					words_buffer[row][i * Number_of_Cols + col] = pgm_read_byte_near(&Alphabet_table[alphabet_index].matrix[row][col]);
				}
			}
		}

		//display this sentence
		for (int j = 0; j <= Number_of_Cols * (words.length() - 1); j++)
		{
			int time_delay = 200;
			for (int Time = 0; Time < time_delay / speed; Time++)
			{
				for (int Col = 1; Col <= 8; Col++)
				{
					digitalWrite(LATCH, LOW);
					shiftOut(SER_COL, CLK_COL, MSBFIRST, 1 << (Col - 1));
					int row_data = 0;
					for (int Row = 1; Row <= 8; Row++)
					{
						row_data = (row_data << 1) + int(words_buffer[Row - 1][j + Col - 1]);
					}
					shiftOut(SER_ROW, CLK_ROW, LSBFIRST, ~row_data);
					digitalWrite(LATCH, HIGH);
				}
			}
		}
	}
	else
	{
		Serial.println("Invalid score!!!");
	}
}


void MATRIX::setText(String text,int speed)
{

	char words_buffer[8][8 * 100];
	text.toUpperCase();

	//use the alphabet unit to make a sentence and storage the sentence into words_buffer
	//For example : GOOD='G'+'O'+'O'+'D'
	for (int i = 0; i < text.length(); i++)
	{
		char current_alphabet = text.charAt(i);
		int alphabet_index = getIndex(current_alphabet);
		for (int row = 0; row < Number_of_Rows; row++)
		{
			for (int col = 0; col < Number_of_Cols; col++)
			{
				words_buffer[row][i * Number_of_Cols + col] = pgm_read_byte_near(&Alphabet_table[alphabet_index].matrix[row][col]);
			}
		}
	}

	//display this sentence
	//keep the sentence still and move the 8*8 matrix slowly.
	for (int j = 0; j <= Number_of_Cols * (text.length() - 1); j++)
	{
		int time_delay = 200;
		for (int Time = 0; Time < time_delay / speed; Time++)
		{
			for (int Col = 1; Col <= 8; Col++)
			{
				digitalWrite(LATCH, LOW);
				shiftOut(SER_COL, CLK_COL, MSBFIRST, 1 << (Col - 1));
				int row_data = 0;
				for (int Row = 1; Row <= 8; Row++)
				{
					row_data = (row_data << 1) + int(words_buffer[Row - 1][j + Col - 1]);
				}
				shiftOut(SER_ROW, CLK_ROW, LSBFIRST, ~row_data);
				digitalWrite(LATCH, HIGH);
			}
		}
	}

}

int MATRIX::getIndex(char alphabet)
{
	for (int i = 0; i < sizeof(Alphabet_table) / sizeof(Alphabet_table[0]); i++)
	{
		if (pgm_read_byte_near(&Alphabet_table[i].alphabet) == alphabet)
		{
			return i;
		}
	}
	return -1;
}