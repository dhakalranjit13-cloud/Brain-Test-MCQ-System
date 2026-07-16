//BRAIN TEST MCQ SYSTEM
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>

// STRUCTURES
struct Question
{
    char genre[100];
    char que[5000];
    char option1[100];
    char option2[100];
    char option3[100];
    char option4[100];
    int ans;
};
struct Score
{
    char name[50];
    char genre[50];
    int score;
    int total;
};
// FUNCTION DECLARATIONS
void signup();
int signin();
void addquestion();
void viewQuestions();
void editQuestion();
void deleteQuestion();
void quiz(char name[]);
void endlessQuiz(char name[]);
void showScorecard();
void shuffleOptions(struct Question *q);

// MAIN FUNCTION
int main()
{
    int choice;
    char name[100];
    srand(time(NULL));
    while(1)
    {
        printf("\n====================================\n");
        printf("      BRAIN TEST MCQ SYSTEM\n");
        printf("====================================\n");
        printf("1. Play Quiz\n");
        printf("2. Admin Panel\n");
        printf("3. Exit\n");
        printf("====================================\n");
        printf("Enter choice: ");
        choice=0;
        scanf("%d", &choice);
        while(getchar() != '\n'); // clean input for next question
        if(choice == 1)
        {
            printf("Enter your name: ");
            scanf(" %[^\n]", name);
            while(getchar() != '\n'); // clean input for next question
            int playChoice;
            while(1)
            {
                printf("\n=========== PLAYER MENU ===========\n");
                printf("1. Quiz\n");
                printf("2. Endless Quiz\n");
                printf("3. Scoreboard\n");
                printf("4. Back\n");
                printf("===================================\n");
                printf("Enter choice: ");
                playChoice = 0;
                scanf("%d", &playChoice);
                while(getchar() != '\n'); // clean input for next question
                if(playChoice == 1)
                {
                    quiz(name);
                }
                else if(playChoice == 2)
                {
                    endlessQuiz(name);
                }
                else if(playChoice == 3)
                {
                    showScorecard();
                }
                else if(playChoice == 4)
                {
                    break;
                }
                else
                {
                    printf("Invalid choice!Please Try Again.\n");
                }
            }
        }
        else if(choice == 2)
        {
            int adminChoice;

            printf("\n=========== ADMIN PANEL ===========\n");
            printf("1. Signup\n");
            printf("2. Signin\n");
            printf("===================================\n");
            printf("Enter choice: ");
            adminChoice=0;
            scanf("%d", &adminChoice);
            while(getchar() != '\n'); // clean input for next question

            if(adminChoice == 1)
            {
                signup();
            }
            else if(adminChoice == 2)
            {
                if(signin() == 1)
                {
                    int adminMenu;

                    while(1)
                    {
                        printf("\n=========== ADMIN MENU ===========\n");
                        printf("1. Add Question\n");
                        printf("2. View Questions\n");
                        printf("3. Edit Question\n");
                        printf("4. Delete Question\n");
                        printf("5. Exit\n");
                        printf("==================================\n");
                        printf("Enter choice: ");
                        adminMenu = 0;
                        scanf("%d", &adminMenu);
                        while(getchar() != '\n'); // clean input for next question

                        if(adminMenu == 1)
                        {
                            addquestion();
                        }
                        else if(adminMenu == 2)
                        {
                            viewQuestions();
                        }
                        else if(adminMenu == 3)
                        {
                            editQuestion();
                        }
                        else if(adminMenu == 4)
                        {
                            deleteQuestion();
                        }
                        else if(adminMenu == 5)
                        {
                            break;
                        }
                        else
                        {
                            printf("Invalid choice!\n");
                        }
                    }
                }
                else
                {
                    printf("Login Failed!\n");
                }
            }
            else
            {
                printf("Invalid choice! Please enter 1 or 2.\n");
            }
        }
        else if(choice == 3)
        {
            printf("Thank You for Playing!\n");
            break;
        }
        else
        {
            printf("Invalid choice!Please Try Again.\n");
        }
    }

    return 0;
}

// ============================================================
// SIGNUP
// ============================================================

void signup()
{
    FILE *fp = fopen("userNpass.txt", "a");

    char user[50], pass[50];

    if(fp == NULL)
    {
        printf("File error!\n");
        return;
    }

    printf("Create Username: ");
    scanf("%s", user);

    printf("Create Password: ");
    scanf("%s", pass);

    fprintf(fp, "%s\n%s\n", user, pass);

    fclose(fp);

    printf("Account Created Successfully!\n");
}
// SIGNIN
int signin()
{
    FILE *fp = fopen("userNpass.txt", "r");
    char user[50], pass[50];
    char fuser[50], fpass[50];
    if(fp == NULL)
    {
        printf("No account found!\n");
        return 0;
    }
printf("Username: ");
scanf("%s", user);
char *temp = getpass("Password: ");
strncpy(pass, temp, 49);
pass[49] = '\0';
printf("\n");
while(fscanf(fp, " %s\n%s\n", fuser, fpass) == 2)
    {
        if(strcmp(user, fuser) == 0 && strcmp(pass, fpass) == 0)
        {
            fclose(fp);
            printf("Login Successful! Welcome, %s!\n", user);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}
// ADD QUESTION
void addquestion()
{
    FILE *fp = fopen("question.txt", "a");
    static struct Question q;
    int choice;
    if(fp == NULL)
    {
        printf("File error!\n");
        return;
    }
    while(1)
    {
        printf("\n1. Geography\n");
        printf("2. Science\n");
        printf("3. History\n");
        printf("4. Sport\n");
        printf("5. Mathematics\n");
        printf("6. General\n");
        printf("0. Exit\n");
        printf("Enter genre choice: ");
        scanf("%d", &choice);
        while(getchar() != '\n'); // clean input for next question
        if(choice == 0)
        {
            break;
        }

        switch(choice)
        {
            case 1: strcpy(q.genre, "Geography");   break;
            case 2: strcpy(q.genre, "Science");     break;
            case 3: strcpy(q.genre, "History");     break;
            case 4: strcpy(q.genre, "Sport");       break;
            case 5: strcpy(q.genre, "Mathematics"); break;
            case 6: strcpy(q.genre, "General");     break;
            default:
                printf("Invalid choice!\n");
                continue;
        }
        printf("Enter Question: ");
        scanf(" %[^\n]", q.que);

        printf("Option 1: ");
        scanf(" %[^\n]", q.option1);

        printf("Option 2: ");
        scanf(" %[^\n]", q.option2);

        printf("Option 3: ");
        scanf(" %[^\n]", q.option3);

        printf("Option 4: ");
        scanf(" %[^\n]", q.option4);

        printf("Correct Answer (1-4): ");
        scanf("%d", &q.ans);
        while(getchar() != '\n'); // clean input for next question

        fprintf(fp, "%s\n%s\n%s\n%s\n%s\n%s\n%d\n",
                q.genre,
                q.que,
                q.option1,
                q.option2,
                q.option3,
                q.option4,
                q.ans);

        printf("Question Added Successfully!\n");
    }

    fclose(fp);
}
// VIEW QUESTIONS
void viewQuestions()
{
    FILE *fp = fopen("question.txt", "r");
    static struct Question q;
    int count = 1;
    if(fp == NULL)
    {
        printf("No questions found!\n");
        return;
    }
    printf("\n============================================================\n");
    printf("                     ALL QUESTIONS\n");
    printf("============================================================\n");

    while(fscanf(fp, " %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %d",
           q.genre, q.que,
           q.option1, q.option2,
           q.option3, q.option4,
           &q.ans) == 7)
    {
        printf("\nQuestion %d  [%s]\n", count, q.genre);
        printf("  Q: %s\n", q.que);
        printf("  1. %s\n", q.option1);
        printf("  2. %s\n", q.option2);
        printf("  3. %s\n", q.option3);
        printf("  4. %s\n", q.option4);
        printf("  Correct Answer: %d\n", q.ans);
        printf("------------------------------------------------------------\n");
        count++;
    }
    if(count == 1)
    {
        printf("No questions available!\n");
    }
    else
    {
        printf("\nTotal Questions: %d\n", count - 1);
    }
    fclose(fp);
}
// DELETE QUESTION
void deleteQuestion()
{
    FILE *fp = fopen("question.txt", "r");
    static struct Question q[200];
    int count = 0;
    if(fp == NULL)
    {
        printf("No questions found!\n");
        return;
    }
    while(fscanf(fp, " %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %d",
           q[count].genre,
           q[count].que,
           q[count].option1,
           q[count].option2,
           q[count].option3,
           q[count].option4,
           &q[count].ans) == 7)
    {
        count++;
    }
    fclose(fp);
    if(count == 0)
    {
        printf("No questions available!\n");
        return;
    }

    printf("\n============================================================\n");
    for(int i = 0; i < count; i++)
    {
        printf("%d. [%s] %s\n", i + 1, q[i].genre, q[i].que);
    }
    printf("============================================================\n");
    int del;
    printf("Enter question number to delete (0 to cancel): ");
    scanf("%d", &del);
    while(getchar() != '\n'); // clean input for next question
    if(del == 0)
    {
        printf("Cancelled.\n");
        return;
    }

    if(del < 1 || del > count)
    {
        printf("Invalid question number!\n");
        return;
    }

    fp = fopen("question.txt", "w");

    if(fp == NULL)
    {
        printf("File error!\n");
        return;
    }

    for(int i = 0; i < count; i++)
    {
        if(i != del - 1)
        {
            fprintf(fp, "%s\n%s\n%s\n%s\n%s\n%s\n%d\n",
                    q[i].genre,
                    q[i].que,
                    q[i].option1,
                    q[i].option2,
                    q[i].option3,
                    q[i].option4,
                    q[i].ans);
        }
    }

    fclose(fp);

    printf("Question %d Deleted Successfully!\n", del);
}
// EDIT QUESTION
void editQuestion()
{
    FILE *fp = fopen("question.txt", "r");
    static struct Question q[200];
    int count = 0;

    if(fp == NULL)
    {
        printf("No questions found!\n");
        return;
    }

    // Read all questions from file
    while(fscanf(fp, " %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %d",
        q[count].genre,
        q[count].que,
        q[count].option1,
        q[count].option2,
        q[count].option3,
        q[count].option4,
        &q[count].ans) == 7)
    {
        count++;
    }
    fclose(fp);

    if(count == 0)
    {
        printf("No questions available!\n");
        return;
    }

    // Show all questions
    printf("\n============================================================\n");
    for(int i = 0; i < count; i++)
    {
        printf("%d. [%s] %s\n", i + 1, q[i].genre, q[i].que);
    }
    printf("============================================================\n");

    // Ask which question to edit
    int edit;
    printf("Enter question number to edit (0 to cancel): ");
    scanf("%d", &edit);
    while(getchar() != '\n'); // clean input for next question
    

    if(edit == 0)
    {
        printf("Cancelled.\n");
        return;
    }

    if(edit < 1 || edit > count)
    {
        printf("Invalid question number!\n");
        return;
    }

    edit--;
    char temp[5000];

    // Edit question
    printf("\nCurrent Question: %s\n", q[edit].que);
    printf("Enter new question (or press Enter to keep): ");
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = '\0'; // remove newline
    if(strlen(temp) > 0) strcpy(q[edit].que, temp);

    // Edit option 1
    printf("Current Option 1: %s\n", q[edit].option1);
    printf("Option 1: ");
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = '\0';
    if(strlen(temp) > 0) strcpy(q[edit].option1, temp);

    // Edit option 2
    printf("Current Option 2: %s\n", q[edit].option2);
    printf("Option 2: ");
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = '\0';
    if(strlen(temp) > 0) strcpy(q[edit].option2, temp);

    // Edit option 3
    printf("Current Option 3: %s\n", q[edit].option3);
    printf("Option 3: ");
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = '\0';
    if(strlen(temp) > 0) strcpy(q[edit].option3, temp);

    // Edit option 4
    printf("Current Option 4: %s\n", q[edit].option4);
    printf("Option 4: ");
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = '\0';
    if(strlen(temp) > 0) strcpy(q[edit].option4, temp);

    // Edit correct answer
    printf("Current Correct Answer: %d\n", q[edit].ans);
    printf("Correct Answer (1-4): ");
    int newAns;
    scanf("%d", &newAns);
    while(getchar() != '\n'); // clean input for next question
    if(newAns >= 1 && newAns <= 4) q[edit].ans = newAns;

    // Save all questions back to file
    fp = fopen("question.txt", "w");
    if(fp == NULL)
    {
        printf("File error!\n");
        return;
    }

    for(int i = 0; i < count; i++)
    {
        fprintf(fp, "%s\n%s\n%s\n%s\n%s\n%s\n%d\n",
            q[i].genre,
            q[i].que,
            q[i].option1,
            q[i].option2,
            q[i].option3,
            q[i].option4,
            q[i].ans);
    }

    fclose(fp);
    printf("Question Updated Successfully!\n");
}
// SHUFFLE OPTIONS
void shuffleOptions(struct Question *q)
{
    char options[4][100];

    snprintf(options[0], sizeof(options[0]), "%s", q->option1);
    snprintf(options[1], sizeof(options[1]), "%s", q->option2);
    snprintf(options[2], sizeof(options[2]), "%s", q->option3);
    snprintf(options[3], sizeof(options[3]), "%s", q->option4);

    int correct = q->ans - 1;

    // Fisher-Yates shuffle (SAFE)
    for(int i = 3; i > 0; i--)
    {
        int j = rand() % (i + 1);

        char temp[100];
        snprintf(temp, sizeof(temp), "%s", options[i]);
        snprintf(options[i], sizeof(options[i]), "%s", options[j]);
        snprintf(options[j], sizeof(options[j]), "%s", temp);

        if(i == correct) correct = j;
        else if(j == correct) correct = i;
    }

    snprintf(q->option1, sizeof(q->option1), "%s", options[0]);
    snprintf(q->option2, sizeof(q->option2), "%s", options[1]);
    snprintf(q->option3, sizeof(q->option3), "%s", options[2]);
    snprintf(q->option4, sizeof(q->option4), "%s", options[3]);

    q->ans = correct + 1;
}
// QUIZ
void quiz(char name[])
{
    FILE *fp = fopen("question.txt", "r");

    if(fp == NULL)
    {
        printf("No questions found!\n");
        return;
    }

    // Load all questions
    struct Question allQ[500];// stored in memory not stack
    int total = 0;

    while (fscanf(fp, " %99[^\n] %4999[^\n] %99[^\n] %99[^\n] %99[^\n] %99[^\n] %d",
        allQ[total].genre,
        allQ[total].que,
        allQ[total].option1,
        allQ[total].option2,
        allQ[total].option3,
        allQ[total].option4,
        &allQ[total].ans) == 7)
    {
        total++;
    }

    fclose(fp);

    if(total == 0)
    {
        printf("No questions available!\n");
        return;
    }

    // Show genre selection
    printf("\n=========== SELECT GENRE ===========\n");
    printf("1. Geography\n");
    printf("2. Science\n");
    printf("3. History\n");
    printf("4. Sport\n");
    printf("5. Mathematics\n");
    printf("6. General\n");
    printf("7. Mixed (All Genres)\n");
    printf("0. Back\n");
    printf("=====================================\n");
    printf("Enter genre choice: ");

    int genreChoice;
    scanf("%d", &genreChoice);
    while(getchar() != '\n'); // clean input for next question
    if(genreChoice == 0)
    {
        return;
    }

    char selectedGenre[50];
    int mixed = 0;

    switch(genreChoice)
    {
        case 1: strcpy(selectedGenre, "Geography");   break;
        case 2: strcpy(selectedGenre, "Science");     break;
        case 3: strcpy(selectedGenre, "History");     break;
        case 4: strcpy(selectedGenre, "Sport");       break;
        case 5: strcpy(selectedGenre, "Mathematics"); break;
        case 6: strcpy(selectedGenre, "General");     break;
        case 7: strcpy(selectedGenre, "Mixed"); mixed = 1; break;
        default:
            printf("Invalid choice!\n");
            return;
    }

    // Filter questions by genre
    struct Question pool[500];
    int poolSize = 0;

    for(int i = 0; i < total; i++)
    {
        if(mixed || strcmp(allQ[i].genre, selectedGenre) == 0)
        {
            pool[poolSize++] = allQ[i];
        }
    }

    if(poolSize == 0)
    {
        printf("No questions found for this genre!\n");
        return;
    }

    // Fisher-Yates shuffle
    for(int i = poolSize - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
       struct Question temp = pool[i];
        pool[i] = pool[j];
        pool[j] = temp;
    }

    // Cap at 10 questions
    int quizSize = poolSize < 10 ? poolSize : 10;

    printf("\n====================================\n");
    printf("  QUIZ START: %s\n", mixed ? "Mixed" : selectedGenre);
    printf("  Total Questions: %d\n", quizSize);
    printf("====================================\n\n");

    int score = 0;

    for(int i = 0; i < quizSize; i++)
    {
        struct Question q = pool[i];
        shuffleOptions(&q);

        printf("Question %d of %d  [%s]\n", i + 1, quizSize, q.genre);
        printf("------------------------------------\n");
        printf("%s\n\n", q.que);
        printf("  1. %s\n", q.option1);
        printf("  2. %s\n", q.option2);
        printf("  3. %s\n", q.option3);
        printf("  4. %s\n", q.option4);
        printf("\nYour answer (1-4): ");

        int ans;
        scanf("%d", &ans); 
        while(getchar() != '\n'); // clean input for next question
        if(ans < 1 || ans > 4)
        {
            printf("  Invalid input! Marked as wrong.\n\n");
        }
        else if(ans == q.ans)
        {
            printf("  CORRECT!\n\n");
            score++;
        }
        else
        {
            printf("  WRONG! Correct answer: %d. %s\n\n", q.ans,
                   q.ans == 1 ? q.option1 :
                   q.ans == 2 ? q.option2 :
                   q.ans == 3 ? q.option3 : q.option4);
        }
    }

    // Result
    float pct = quizSize > 0 ? (float)score / quizSize * 100 : 0; // avoid divide by zero
    char grade[20];

    if(pct >= 90)      strcpy(grade, "EXCELLENT!");
    else if(pct >= 70) strcpy(grade, "GOOD JOB!");
    else if(pct >= 50) strcpy(grade, "KEEP TRYING!");
    else               strcpy(grade, "NEEDS IMPROVEMENT");

    printf("====================================\n");
    printf("         QUIZ RESULT\n");
    printf("====================================\n");
    printf("  Player : %s\n", name);
    printf("  Genre  : %s\n", mixed ? "Mixed" : selectedGenre);
    printf("  Score  : %d / %d\n", score, quizSize);
    printf("  Grade  : %.1f%% - %s\n", pct, grade);
    printf("====================================\n");

    // Save to scoreboard
    FILE *sf = fopen("scoreboard.txt", "a");

    if(sf != NULL)
    {
        fprintf(sf, "%s\n%s\n%d\n%d\n",
                name,
                mixed ? "Mixed" : selectedGenre,
                score,
                quizSize);
        fclose(sf);
    }
}
// ENDLESS QUIZ
void endlessQuiz(char name[])
{
    FILE *fp = fopen("question.txt", "r");

    if(fp == NULL)
    {
        printf("No questions found!\n");
        return;
    }

    static struct Question allQ[500];   // static: avoids stack overflow
    int total = 0;

    while(total < 500 &&
        fscanf(fp,
            " %99[^\n] %4999[^\n] %99[^\n] %99[^\n] %99[^\n] %99[^\n] %d",
            allQ[total].genre,
            allQ[total].que,
            allQ[total].option1,
            allQ[total].option2,
            allQ[total].option3,
            allQ[total].option4,
            &allQ[total].ans) == 7)
    {
        total++;
    }

    fclose(fp);

    if(total == 0)
    {
        printf("No questions available!\n");
        return;
    }

    printf("\n====================================\n");
    printf("       ENDLESS QUIZ MODE\n");
    printf("====================================\n");
    printf("  Answer correctly to keep going!\n");
    printf("  One wrong answer ends the game.\n");
    printf("  Enter 0 to quit at any time.\n");
    printf("====================================\n\n");

    int score = 0;
    int asked = 0;

    // Initial Fisher-Yates shuffle
    for(int i = total - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        struct Question temp = allQ[i];
        allQ[i] = allQ[j];
        allQ[j] = temp;
    }

    while(1)
    {
        // Reshuffle when all questions are exhausted
        if(asked >= total)
        {
            printf("\n  All questions completed! Reshuffling...\n\n");
            for(int i = total - 1; i > 0; i--)
            {
                int j = rand() % (i + 1);
                struct Question temp = allQ[i];
                allQ[i] = allQ[j];
                allQ[j] = temp;
            }
            asked = 0;
        }

        struct Question q = allQ[asked];
        shuffleOptions(&q);

        printf("------------------------------------\n");
        printf("Question #%d  |  Score: %d  |  [%s]\n", asked + 1, score, q.genre);
        printf("------------------------------------\n");
        printf("%s\n\n", q.que);
        printf("  1. %s\n", q.option1);
        printf("  2. %s\n", q.option2);
        printf("  3. %s\n", q.option3);
        printf("  4. %s\n", q.option4);
        printf("\nYour answer (1-4, or 0 to quit): ");

        int ans;
        if(scanf("%d", &ans) != 1)
        {
            while(getchar() != '\n' && !feof(stdin)); // clear bad input
            printf("  Invalid input! Counted as wrong.\n");
            printf("\n  GAME OVER!\n");
            break;
        }
        while(getchar() != '\n'); // clean input for next question

        if(ans == 0)
        {
            printf("\n  You quit the endless quiz.\n");
            break;
        }

        if(ans < 1 || ans > 4)
        {
            printf("  Invalid input! Counted as wrong.\n");
            printf("\n  GAME OVER!\n");
            break;
        }
        else if(ans == q.ans)
        {
            score++;
            asked++;
            printf("  CORRECT! Keep going! (Score: %d)\n\n", score);
        }
        else
        {
            printf("  WRONG! Correct answer was: %d. %s\n", q.ans,
                q.ans == 1 ? q.option1 :
                q.ans == 2 ? q.option2 :
                q.ans == 3 ? q.option3 : q.option4);
            printf("\n  GAME OVER!\n");
            break;
        }
    }

    // Final result
    char grade[20];
    if(score >= 20)      strcpy(grade, "LEGENDARY!");
    else if(score >= 10) strcpy(grade, "IMPRESSIVE!");
    else if(score >= 5)  strcpy(grade, "GOOD START!");
    else                  strcpy(grade, "KEEP PRACTICING!");

    printf("\n====================================\n");
    printf("     ENDLESS QUIZ RESULT\n");
    printf("====================================\n");
    printf("  Player     : %s\n", name);
    printf("  Final Score: %d\n", score);
    printf("  Grade      : %s\n", grade);
    printf("====================================\n");

    // Save to scoreboard (total = score since it's endless)
    FILE *sf = fopen("scoreboard.txt", "a");

    if(sf != NULL)
    {
        fprintf(sf, "%s\nEndless\n%d\n%d\n",
            name,
            score,
            score > 0 ? score : 1);
        fclose(sf);
    }
}
// SCOREBOARD
void showScorecard()
{
    FILE *fp = fopen("scoreboard.txt", "r");

    if(fp == NULL)
    {
        printf("\nNo scores recorded yet!\n");
        return;
    }

    struct Score scores[500];
    int count = 0;

    while(fscanf(fp, " %[^\n] %[^\n] %d %d",
           scores[count].name,
           scores[count].genre,
           &scores[count].score,
           &scores[count].total) == 4)
    {
        count++;
    }

    fclose(fp);

    if(count == 0)
    {
        printf("\nNo scores recorded yet!\n");
        return;
    }

    // Bubble sort by score descending
    for(int i = 0; i < count - 1; i++)
    {
        for(int j = 0; j < count - i - 1; j++)
        {
            float pctA = (float)scores[j].score / scores[j].total * 100;
            float pctB = (float)scores[j+1].score / scores[j+1].total * 100;

            if(pctA < pctB)
            {
                struct Score temp = scores[j];
                scores[j] = scores[j+1];
                scores[j+1] = temp;
            }
        }
    }

    printf("\n");
    printf("============================================================\n");
    printf("                     SCOREBOARD                            \n");
    printf("============================================================\n");
    printf("%-5s %-15s %-14s %-10s %-7s\n",
           "Rank", "Name", "Genre", "Score", "Pct");
    printf("------------------------------------------------------------\n");

    for(int i = 0; i < count; i++)
    {
        float pct;
        char medal[5];

        // Prevent division by zero
        if(scores[i].total == 0)
            pct = 0;
        else
            pct = (float)scores[i].score / scores[i].total * 100;

        if(i == 0)      strcpy(medal, "[1]");
        else if(i == 1) strcpy(medal, "[2]");
        else if(i == 2) strcpy(medal, "[3]");
        else            sprintf(medal, "%d", i + 1);

        printf("%-5s %-15s %-14s %d/%-7d %.1f%%\n",
               medal,
               scores[i].name,
               scores[i].genre,
               scores[i].score,
               scores[i].total,
               pct);
    }

    printf("============================================================\n");
    printf("  Total Records: %d\n", count);
    printf("============================================================\n");
}
