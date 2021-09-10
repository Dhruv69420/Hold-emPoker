#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
int n, pot = 0;
void printtable(int turn, char **names, char *cards[n][2], int points[], int bets[])
{
    for (int i = 0; i < n; i++)
    {

        if (i + 1 == turn)
        {
            printf("%s %s %s %d %d\n", names[i], cards[i][0], cards[i][1], points[i], bets[i]);
        }
        else
            printf("%s %s %s %d %d\n", names[i], cards[i][0], cards[i][1], points[i], bets[i]);
    }
}
void deleteplayer(int mark, char **names, char *cards[n][2], int points[], int bets[])
{
    if (mark == n - 1)
    {
        --n;
    }
    else
    {
        for (int i = mark; i < n - 1; i++)
        {
            names[i] = names[i + 1];
            cards[i][0] = cards[i + 1][0];
            cards[i][1] = cards[i + 1][1];
            points[i] = points[i + 1];
            bets[i] = bets[i + 1];
        }

        --n;
    }
}

void round(int *max, int turn, char **names, char *cards[n][2], int points[], int bets[])
{
    int out = 0;
    while (out != 1)
    {
        out = 1;
        for (int i = 0; i < n; i++)
        {

            int mark = 0;
            if (bets[i] == *max)
            {
                out = 1;
                points[i] -= bets[i];
                break;
            }

            printf("%s Place your bet: ", names[i]);
            scanf("%d", &bets[i]);
            if (bets[i] > *max)
            {
                *max = bets[i];
                out = 0;
            }
            else if (bets[i] < *max)
            {
                while (1)
                {
                    if (bets[i] == -1)
                    {

                        deleteplayer(i, names, cards, points, bets);

                        if (i == n)
                        {

                            break;
                        }
                        printf("%s Place your bet: ", names[i]);
                        scanf("%d", &bets[i]);
                    }
                    if (bets[i] != -1 && bets[i] < *max)
                    {
                        printf("%s Enter a valid bet", names[i]);
                        scanf("%d", &bets[i]);
                        continue;
                    }
                    else
                    {
                        points[i] -= bets[i];
                        break;
                    }
                }
            }
            else if (bets[i + 1] == bets[i])
            {
                points[i] -= bets[i];
                out = 1;
                break;
            }

            points[i] -= bets[i];
            pot += bets[i];

            printtable(turn, names, cards, points, bets);
        }
    }
}

void deletecard(char **deck, int ind, int *deckn)
{

    while (ind < (*deckn - 1))
    {
        deck[ind] = deck[ind + 1];
        ind++;
    }
    --(*deckn);

    
}
void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}
int suits(char *arr[n][7], int i)
{
    int flag = 1;
    char *c;
    char *c1;
    for (int j = 0; j < 6; j++)
    {
        c = arr[i][j];
        c1 = arr[i][j + 1];
        if (c[2] != c1[2])
        {
            flag = 0;
            break;
        }
    }
    return flag;
}
void decision(char **dealer_cards, char *cards[n][2], char **names)
{

    char *arr[n][7];
    int result[n];
    for (int i = 0; i < n; i++)
    {
        arr[i][0] = cards[i][0];
        arr[i][1] = cards[i][1];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 2; j < 7; j++)
        {
            arr[i][j] = dealer_cards[j - 2];
        }
    }

    for (int i = 0; i < n; i++)
    {
        int check = 0, flag = 0;
        char *c;
        char *c1;
        for (int j = 0; j < 7; j++)
        {
            c = arr[i][j];

            if (c[1] == 'A')
                check++;

            if (c[1] == 'K')
                check++;

            if (c[1] == 'Q')
                check++;

            if (c[1] == 'J')
                check++;

            if (c[0] == '1')
                check++;
        }
        if (check == 5)
        {

            if (suits(arr, i))
            {
                result[i] = 1;
                flag = 0;
                continue;
            }
            else
            {
                flag = 0;
                result[i] = 6;
                continue;
            }
        }
        else
        {

            for (int j = 0; j < 6; j++)
            {
                c = arr[i][j];
                c1 = arr[i][j + 1];
                if (c[1] != c1[1] + 1)
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
            {
                if (suits(arr, i))
                {
                    result[i] = 2;
                    continue;
                }
                else
                {
                    result[i] = 6;
                    continue;
                }
            }

            else
            {
                flag = 0;
            }
        }
        int trip = 0, doub = 0;
        int fr[7];
        for (int j = 0; j < 7; j++)
        {
            int count = 1;
            c = arr[i][j];

            for (int k = j + 1; k < 7; k++)
            {
                c1 = arr[i][k];
                if (c[1] == c1[1])
                {
                    count++;
                    fr[k] = -1;
                }
            }
            if (fr[j] != -1)
                fr[j] = count;
        }

        for (int j = 0; j < 7; j++)
        {

            if (fr[j] == 4)
            {
                result[i] = 3;
                flag = 1;
                break;
            }

            else if (fr[j] == 3)
            {
                trip++;
                continue;
            }
            else if (fr[j] == 2)
            {

                doub++;
                continue;
            }
            
        }

        if (flag == 1)
        {
            flag = 0;
            break;
        }
        else if ((trip > 1) || (trip > 0 && doub > 0))
        {
            result[i] = 4;
            flag = 0;
            continue;
        }
        else if (trip == 1 && doub == 0)
        {
            result[i] = 7;
            flag = 0;
            continue;
        }
        else if (trip == 0 && doub == 2)
        {

            result[i] = 8;
            flag = 0;
            continue;
        }
        else if (trip == 0 && doub == 1)
        {
            result[i] = 9;
            flag = 0;
            continue;
        }

        if (suits(arr, i))
        {
            result[i] = 5;
            flag = 0;
            continue;
        }
        int seq = 0;
        for (int j = 0; j < 6; j++)
        {
            c = arr[i][j];
            c1 = arr[i][j + 1];
            if (c[1] != c1[1] + 1)
            {
                seq = 1;
                break;
            }
        }
        if (seq == 0)
        {
            result[i] = 6;
            flag = 0;
            continue;
        }

        result[i] = 10;
    }
    int min = result[0];
    int ind = 0;
    for (int i = 1; i < n; i++)
    {
        if (result[i] < min)
        {
            min = result[i];
            ind = i;
        }
    }
    printf("%s is the WINNER taking away the POT with %d POINTS", names[ind], pot);
}
int main()
{

    printf("Enter the number of players- ");
    scanf("%d", &n);
    char *names[n];
    for (int i = 0; i < n; i++)
    {
        names[i] = malloc(50 * sizeof(char));
        printf("P%d Enter your name- ", i + 1);
        scanf("%s", names[i]);
    }

    char *deck[53] = {" AS", " 2S", " 3S", " 4S", " 5S", " 6S", " 7S", " 8S", " 9S", "10S", " JS", " QS", " KS", " AC", " 2C", " 3C", " 4C", " 5C", " 6C", " 7C", " 8C", " 9C", "10C", " JC", " QC", " KC", " AH", " 2H", " 3H", " 4H", " 5H", " 6H", " 7H", " 8H", " 9H", "10H", " JH", " QH", " KH", " AD", " 2D", " 3D", " 4D", " 5D", " 6D", " 7D", " 8D", " 9D", "10D", " JD", " QD", " KD"};
    int cardindex = 0;
    char *cards[n][2];
    int deckn = 53;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < 2; j++)
        {
            cardindex = (rand() % (deckn + 1));
            cards[i][j] = deck[cardindex];
            deletecard(deck, cardindex, &deckn);
        }

    int bets[n];
    int points[n];
    for (int i = 0; i < n; i++)
    {
        points[i] = 1000;
        bets[i] = 0;
    }

    int turn = 1;

    printtable(turn, names, cards, points, bets);

    printf("PRE FLOP ROUND\n");

    for (int i = 0; i < n; i++)
    {

        printf("%s Place your bet: ", names[i]);
        scanf("%d", &bets[i]);
        if (i == 1)
        {

            while (1)
            {
                if (bets[i] != 2 * bets[0])
                {
                    printf("%s Enter a valid bet", names[i]);
                    scanf("%d", &bets[i]);
                    continue;
                }
                else
                    break;
            }
        }

        if (i > 1)
        {

            while (1)
            {
                if (bets[i] == -1)
                {

                    deleteplayer(i, names, cards, points, bets);

                    if (i == n)
                    {

                        break;
                    }
                    printf("%s Place your bet: ", names[i]);
                    scanf("%d", &bets[i]);
                }
                if (bets[i] < bets[i - 1])
                {
                    printf("%s Enter a valid bet", names[i]);
                    scanf("%d", &bets[i]);
                    continue;
                }
                else
                    break;
            }
        }
        points[i] -= bets[i];
        pot += bets[i];

        printtable(turn, names, cards, points, bets);
        
    }

    int max = bets[n - 1];
    printf("\nPRE FlOP ROUND\n");
    printf("\n");
    round(&max, turn, names, cards, points, bets);
    for (int i = 0; i < n; i++)
        bets[i] = 0;

    printf("\n THE FLOP : ");
    char *dealer_cards[5];
    for (int i = 0; i < 5; i++)
    {
        if (i > 2)
            dealer_cards[i] = "0";
        else
        {
            cardindex = (rand() % (deckn + 1));
            dealer_cards[i] = deck[cardindex];
            printf(" %s ", dealer_cards[i]);
            deletecard(deck, cardindex, &deckn);
        }
    }
    printf("\n");
    printf("\n POST FLOP ROUND\n");
    printf("\n");
    round(&max, turn, names, cards, points, bets);
    printf("THE TURN\n");
    for (int i = 0; i < n; i++)
        bets[i] = 0;

    cardindex = (rand() % (deckn + 1));
    dealer_cards[3] = deck[cardindex];
    for (int i = 0; i < 4; i++)
        printf(" %s ", dealer_cards[i]);
    deletecard(deck, cardindex, &deckn);
    printf("\n");
    printf("\nPOST TURN ROUND\n");
    printf("\n");
    round(&max, turn, names, cards, points, bets);
    printf("THE RIVER\n");

    for (int i = 0; i < n; i++)
        bets[i] = 0;
    cardindex = (rand() % (deckn + 1));
    dealer_cards[4] = deck[cardindex];
    for (int i = 0; i < 5; i++)
        printf(" %s ", dealer_cards[i]);

    deletecard(deck, cardindex, &deckn);
    printf("\n");

    printf("\nPOST RIVER ROUND\n");
    printf("\n");
    round(&max, turn, names, cards, points, bets);

    decision(dealer_cards, cards, names);
}
