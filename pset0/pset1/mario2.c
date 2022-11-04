#include <stdio.h>
#include <cs50.h>
#include <math.h>

int printblocks(int b);

int main(void)
{
    int height;
    do
    {
        height = get_int("select a height: ");
    }
    while( height <= 1 || height >= 8);
    int spaces = height - 1;
    int blockes = 1;
    for(int i=0; i<= height-1; i++)
    {
        for(int j=0; j<= spaces-1; j++)
        {
            printf(" ");
        }
        printblocks(blockes);
        printf(" ");
        printblocks(blockes);
        printf("\n");
        blockes++;
        spaces--;
    }

}

int printblocks(int b)
{
    for(int k=0; k<= b-1; k++)
        {
            printf("#");
        }
        return b;
}