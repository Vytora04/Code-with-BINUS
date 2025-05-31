//#1 Counting by actual available ball to input
#include <stdio.h>

int main()
{
    //Declare variable;
    int n;
    scanf("%d", &n); // Read the input value N.

    //Constants of max shelf capacity (25x25x25) and the ball diameter 7. 3 balls by lenght, wide, and height
    int capacitybox = 27; // Maximum balls a box can hold (3x3x3)

    //Calculate the number of boxes needed.
    int neededbox = (n + capacitybox - 1) / capacitybox;
    //(N + capacitybox - 1) to round up the division

    //Print the results
    printf("%d\n", neededbox);

    return 0;
}


////#2: Counting by volume
//#include<stdio.h>
//#include<math.h>
//
//int main()
//{
//  //Input the number of ball
//  int n, nb;
//  scanf("%d", &n);
//
//  //Calculate ball volume
//  double v = 4 / 3 * 22 / 7 * 7 * 7 * 7;
//
//  //Calculate the needed box for the ball input
//  nb = (ceil(n * v / (25 / 25 / 25)));
//
//  //Print to the screen
//  printf("%d\n", nb);
//
//  return 0;
//}
