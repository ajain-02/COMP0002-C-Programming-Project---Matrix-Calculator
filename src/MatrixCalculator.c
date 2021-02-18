#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

    int nrows;
    int ncolumns;
    int ** matrix;

    int ** empty_double_pointer_for_menu;
    int ** empty_double_pointer_for_menu1;

    int Show_Menu();
    void option_repeat();
    void doOption(int );
    void matrix_load_from_file(int ** , int ** );
    void matrix_save_to_file(int ** );
    void matrix_add();
    void matrix_subtract();
    void matrix_transpose();
    void matrix_multiply();
    void matrix_determinant();
    void matrix_multiply_by_scalar();
    void matrix_inversion();
    int ** initalise_matrix(int* , int* );
    int ** initalise_matrix_without_input(int* , int* );

int Show_Menu(){
    //This is the function that will print out the Menu on the terminal, allowing the user to enter a number of the option they pick and then returns it
    int option_to_be_carried_out;
    printf("MATRIX CALCULATOR\n");
    printf("--------------------\n");
    printf("Please select the option: \n\n1. Load Matrices from File\n2. Save Matrices to File\n3. Add 2 Matrices\n4. Subtract 2 Matrices\n5. Multiply 2 Matrices\n6. Multiply a Matrix by a Scalar\n7. Do the Transpose of a Matrix\n8. Find the Determinant of 3x3 Matrix\n9. Invert a 3x3 Matrix\n10. Quit\n");
    printf("\nOption: ");
    scanf("%d", &option_to_be_carried_out);
    printf("\n");

    return option_to_be_carried_out;
}

void option_repeat(){
    //This function will loop through the Show_Menu() and the doOption() function until the user enters 7 to quit the program.
    while(true){
        int option = Show_Menu();
        doOption(option);
    }
}

void doOption(int option){
    //This function will take the user-selected option in as a argument and then using the switch case statements, will carry out the appropriate task
    switch (option){
        case 1:
            matrix_load_from_file(empty_double_pointer_for_menu, empty_double_pointer_for_menu1);
            break;
        case 2:
            matrix_save_to_file(matrix);
            break;
        case 3:
            matrix_add();
            break;
        case 4:
            matrix_subtract();
            break;
        case 5:
            matrix_multiply();
            break;
        case 6:
            matrix_multiply_by_scalar();
            break;
        case 7:
            matrix_transpose();
            break;
        case 8:
            matrix_determinant();
            break;
        case 9:
            matrix_inversion();
            break;
        case 10:
            exit(1);
            break;
    }
}

void matrix_load_from_file(int ** firstMatrix, int ** secondMatrix){
    FILE *fp;

    int row = 0, col = 0;

    int empty_intialiser_for_rows_1;
    int empty_intialiser_for_columns_1;
    // An empty 2d array will be intialised by calling the function and just allocating memory to it, this is for the first matrix
    int ** first = initalise_matrix_without_input(&empty_intialiser_for_rows_1, &empty_intialiser_for_columns_1);

    //same process as above, but for the second matrix
    int empty_intialiser_for_rows_2;
    int empty_intialiser_for_columns_2;
    int ** second = initalise_matrix_without_input(&empty_intialiser_for_rows_2, &empty_intialiser_for_columns_2);


    int count = 0;
    fp = fopen("../Data Files/MatricesStore.txt","r");

    //Scans the file for an integer and then assigns it to the relevant position in the 2d array/matrix - for the first matrix
    for(int i = 0; i < empty_intialiser_for_rows_1; i++){
        for (int j = 0; j < empty_intialiser_for_columns_1; j++){
            fscanf(fp, "%d", &first[i][j]);
       }
    }

    //Scans the file for an integer and then assigns it to the relevant position in the 2d array/matrix - for the second matrix
    for(int i = 0; i < empty_intialiser_for_rows_2; i++){
        for (int j = 0; j < empty_intialiser_for_columns_2; j++){
            fscanf(fp, "%d", &second[i][j]);
       }
    }

    //Prints the matrix on the terminal - for the first matrix
    printf("\nFirst matrix loaded from File 'MatricesStore.txt': ");
    for(int i = 0; i < empty_intialiser_for_rows_1; i++){
        for (int j = 0; j < empty_intialiser_for_columns_1; j++){
            printf("%d ", first[i][j]);
       }
       printf("\n");
    }
    printf("\n");       

    //Prints the matrix on the terminal - for the second matrix
    printf("Second matrix loaded from File 'MatricesStore.txt': ");
    for(int i = 0; i < empty_intialiser_for_rows_2; i++){
        for (int j = 0; j < empty_intialiser_for_columns_2; j++){
            printf("%d ", second[i][j]);
       }
       printf("\n");
    }

    printf("\n"); 
    //These double pointers allow more than 1 variable to be returned, by passing them as empty into the function as arguments and then assigning them to the end product
    firstMatrix = first;
    secondMatrix = second; 

    free(first);
    free(second);
}

void matrix_save_to_file(int ** matrix){
    // An empty 2d array will be intialised by calling the function and just allocating memory to it
    int empty_intialiser_for_rows_1;
    int empty_intialiser_for_columns_1;
    int ** firstMatrix = initalise_matrix(&empty_intialiser_for_rows_1, &empty_intialiser_for_columns_1);

    // Using a file pointer called fp, we open the file in a+ mode, meaning the file can be read and appended on
    FILE *fp = fopen("../Data Files/MatricesStore.txt", "a+");
    fprintf(fp, "\n\nNew Matrices Written to File:\n");
    
    // Adds the matrix that we just initialsed above to the file using fprintf
    for(int i = 0; i < empty_intialiser_for_rows_1; i++){
        for(int j = 0; j < empty_intialiser_for_columns_1; j++){
            fprintf(fp, "%d ", firstMatrix[i][j]);
        }
        fprintf(fp, "\n");
    }
}

void matrix_add(){

    // An empty 2d array will be intialised by calling the function and just allocating memory to it, this is for the first matrix
    int empty_intialiser_for_rows_1;
    int empty_intialiser_for_columns_1;
    int ** firstMatrix = initalise_matrix(&empty_intialiser_for_rows_1, &empty_intialiser_for_columns_1);

    //same process as above, but for the second matrix
    int empty_intialiser_for_rows_2;
    int empty_intialiser_for_columns_2;
    int ** secondMatrix = initalise_matrix(&empty_intialiser_for_rows_2, &empty_intialiser_for_columns_2);

    // create a third double pointer which will be the matrix in which we store the result of our operation
    int** resultMatrix;

    // Using malloc, dynamically allocates memory to the double pointer as a whole
    resultMatrix = malloc(nrows * sizeof(int *));

    // Using malloc, dynamically allocates memory to each row of the double pointer
    for(int i = 0; i < nrows; i++){
        resultMatrix[i] = malloc(ncolumns * sizeof(int));
    }

    for(int i = 0; i < nrows; i++){
        for (int k = 0; k < ncolumns; k++){
            resultMatrix[i][k] = firstMatrix[i][k] + secondMatrix[i][k];
        }
        printf("\n");
    }

    printf("\nResult of the Addition of the 2 Matrices: \n");
    for(int w = 0; w < nrows; w++){
        for (int q = 0; q < ncolumns; q++){
            printf("%d ", resultMatrix[w][q]);
        }
        printf("\n");
    }
    printf("\n");

    free(firstMatrix);
    free(secondMatrix);
    free(resultMatrix);
}

void matrix_subtract(){
    
    // An empty 2d array will be intialised by calling the function and just allocating memory to it, this is for the first matrix
    int empty_intialiser_for_rows_1;
    int empty_intialiser_for_columns_1;
    int ** firstMatrix = initalise_matrix(&empty_intialiser_for_rows_1, &empty_intialiser_for_columns_1);

    //same process as above, but for the second matrix
    int empty_intialiser_for_rows_2;
    int empty_intialiser_for_columns_2;
    int ** secondMatrix = initalise_matrix(&empty_intialiser_for_rows_2, &empty_intialiser_for_columns_2);
    
    // create a third double pointer which will be the matrix in which we store the result of our operation
    int** resultMatrix;

   // Using malloc, dynamically allocates memory to the double pointer as a whole
    resultMatrix = malloc(nrows * sizeof(int *));

    // Using malloc, dynamically allocates memory to each row of the double pointer
    for(int i = 0; i < nrows; i++){
        resultMatrix[i] = malloc(ncolumns * sizeof(int));
    }

    for(int i = 0; i < nrows; i++){
        for (int k = 0; k < ncolumns; k++){
            resultMatrix[i][k] = firstMatrix[i][k] - secondMatrix[i][k];
        }
        printf("\n");
    }

    printf("\nResult of the Subtraction of the 2 Matrices: \n");
    for(int w = 0; w < nrows; w++){
        for (int q = 0; q < ncolumns; q++){
            printf("%d ", resultMatrix[w][q]);
        }
        printf("\n");
    }
    printf("\n");

    free(firstMatrix);
    free(secondMatrix);
    free(resultMatrix);
}

void matrix_transpose(){
// This function initalises a matrix and then does the transpose of it, by assigning the matrix backwards into another new matrix
    
    // An empty 2d array will be intialised by calling the function and just allocating memory to it, this is for the first matrix
    int empty_intialiser_for_rows_1;
    int empty_intialiser_for_columns_1;
    int ** first = initalise_matrix(&empty_intialiser_for_rows_1, &empty_intialiser_for_columns_1);

    // create a third double pointer which will be the matrix in which we store the result of our operation
    int** transposedMatrix;

    // Using malloc, dynamically allocates memory to the double pointer as a whole
    transposedMatrix = malloc(nrows * sizeof(int *));

    // Using malloc, dynamically allocates memory to each row of the double pointer
    for(int i = 0; i < nrows; i++){
        transposedMatrix[i] = malloc(ncolumns * sizeof(int));
    }
    

    for (int i = 0; i < ncolumns; i++){
        for (int j = 0; j < nrows; j++){
            transposedMatrix[i][j] = first[j][i];
        }
    }

    printf("\nTransposed Matrix \n");
    
    for (int i = 0; i < ncolumns; i++){
        for (int j = 0; j < nrows; j++){
            printf("%d ", transposedMatrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    //free the memory allocated by the first and transposedMatrix double pointers since those are not required anymore
    free(first);
    free(transposedMatrix);
}

int ** initalise_matrix(int* number_of_rows, int* number_of_columns){
// This function intialises the new matrix by first dynamically allocating memory to the double pointer using malloc then asks the user to enter in the values of the matrix
    printf("Please enter dimensions of matrix: ");
    printf("\nNumber of rows of matrix: ");
    scanf("%d", &nrows);
    printf("Number of columns of matrix: ");
    scanf("%d", &ncolumns);
    printf("\n");

    *number_of_rows = nrows;
    *number_of_columns = ncolumns;

    int ** initialisedMatrix = NULL;

    initialisedMatrix = malloc(nrows * sizeof(int *));

    for(int i = 0; i < nrows; i++){
        initialisedMatrix[i] = malloc(ncolumns * sizeof(int));
    }

    int new_value;
    for(int i = 0; i < nrows; i++){
        for(int j = 0; j < ncolumns; j++){
            printf("Enter the [%d][%d] value for the matrix: ", i, j);
            scanf("%d", &new_value);
            initialisedMatrix[i][j] = new_value;
        }
    }
    return initialisedMatrix;
}

int ** initalise_matrix_without_input(int* number_of_rows, int* number_of_columns){
// This function intialises the new matrix by dynamically allocating memory to the double pointer using malloc but leaves it empty (to be used for the matrix_load_from_file() function)
    printf("Please enter dimensions of matrix: ");
    printf("\nNumber of rows of matrix: ");
    scanf("%d", &nrows);
    printf("Number of columns of matrix: ");
    scanf("%d", &ncolumns);

    *number_of_rows = nrows;
    *number_of_columns = ncolumns;

    int ** initialisedMatrix = NULL;

    initialisedMatrix = malloc(nrows * sizeof(int *));

    for(int i = 0; i < nrows; i++){
        initialisedMatrix[i] = malloc(ncolumns * sizeof(int));
    }

    return initialisedMatrix;
}

void matrix_multiply(){
    int empty_intialiser_for_rows_1;
    int empty_intialiser_for_columns_1;
    int empty_intialiser_for_rows_2;
    int empty_intialiser_for_columns_2;

    int ** firstMatrix = initalise_matrix(&empty_intialiser_for_rows_1, &empty_intialiser_for_columns_1);
    int ** secondMatrix = initalise_matrix(&empty_intialiser_for_rows_2, &empty_intialiser_for_columns_2);
    int ** resultMatrix;

    resultMatrix = malloc(empty_intialiser_for_rows_1 * sizeof(int *));

    for(int i = 0; i < nrows; i++){
        resultMatrix[i] = malloc(empty_intialiser_for_columns_2 * sizeof(int));
    }

    int sum = 0;

    for (int c = 0 ; c < empty_intialiser_for_rows_1 ; c++ ){
        for (int d = 0 ; d < empty_intialiser_for_columns_2 ; d++ ){
            for (int k = 0 ; k < empty_intialiser_for_columns_1 ; k++ ){
                sum = sum + firstMatrix[c][k]*secondMatrix[k][d];
            }
        resultMatrix[c][d] = sum;
        sum = 0;
        }
    }

    for(int w = 0; w < empty_intialiser_for_rows_1; w++){
        for (int q = 0; q < empty_intialiser_for_columns_2; q++){
            printf("%d ", resultMatrix[w][q]);
        }
        printf("\n");
    }
    printf("\n");
    free(resultMatrix);
}

void matrix_determinant(){
    int empty_intialiser_for_rows_1;
    int empty_intialiser_for_columns_1;
    int ** firstMatrix = initalise_matrix(&empty_intialiser_for_rows_1, &empty_intialiser_for_columns_1);

    long determinant;

    determinant = firstMatrix[0][0] * ((firstMatrix[1][1]*firstMatrix[2][2]) - (firstMatrix[2][1]*firstMatrix[1][2])) -firstMatrix[0][1] * (firstMatrix[1][0] * firstMatrix[2][2] - firstMatrix[2][0] * firstMatrix[1][2]) + firstMatrix[0][2] * (firstMatrix[1][0] * firstMatrix[2][1] - firstMatrix[2][0] * firstMatrix[1][1]);
   
    printf("\nDeterminant of this matrix is %ld\n", determinant);
}

void matrix_multiply_by_scalar(){

    int empty_intialiser_for_rows_1;
    int empty_intialiser_for_columns_1;
    int ** firstMatrix = initalise_matrix(&empty_intialiser_for_rows_1, &empty_intialiser_for_columns_1);

    int ** resultMatrix;
    int scale_factor;

    printf("\nPlease enter factor to mulitply by: ");
    scanf("%d", &scale_factor);

    resultMatrix = malloc(empty_intialiser_for_rows_1 * sizeof(int *));

    for(int i = 0; i < nrows; i++){
        resultMatrix[i] = malloc(empty_intialiser_for_columns_1 * sizeof(int));
    }

    for (int i = 0; i < empty_intialiser_for_rows_1; i++){
        for (int j = 0; j < empty_intialiser_for_columns_1; j++){
            resultMatrix[i][j] = scale_factor*firstMatrix[i][j];
        }
    }
    printf("\n");
    for (int i = 0; i < empty_intialiser_for_rows_1; i++){
        for (int j = 0; j < empty_intialiser_for_columns_1; j++){
            printf("%d ", resultMatrix[i][j]);
        }
        printf("\n");
    }
    free(resultMatrix);
}

void matrix_inversion(){
    int empty_intialiser_for_rows_1;
    int empty_intialiser_for_columns_1;
    int ** firstMatrix = initalise_matrix(&empty_intialiser_for_rows_1, &empty_intialiser_for_columns_1);
    double ** resultMatrix;

    resultMatrix = malloc(empty_intialiser_for_rows_1 * sizeof(int *));

    for(int i = 0; i < empty_intialiser_for_rows_1; i++){
        resultMatrix[i] = malloc(empty_intialiser_for_columns_1 * sizeof(int));
    }
    double determinant;

    determinant = firstMatrix[0][0] * ((firstMatrix[1][1]*firstMatrix[2][2]) - (firstMatrix[2][1]*firstMatrix[1][2])) -firstMatrix[0][1] * (firstMatrix[1][0]* firstMatrix[2][2] - firstMatrix[2][0] * firstMatrix[1][2]) + firstMatrix[0][2] * (firstMatrix[1][0] * firstMatrix[2][1] - firstMatrix[2][0] * firstMatrix[1][1]);

    for (int i = 0; i < empty_intialiser_for_rows_1; i++){
        for (int j = 0; j < empty_intialiser_for_columns_1; j++){
            resultMatrix[i][j] = ((firstMatrix[(j+1)%3][(i+1)%3] * firstMatrix[(j+2)%3][(i+2)%3]) - (firstMatrix[(j+1)%3][(i+2)%3] * firstMatrix[(j+2)%3][(i+1)%3]))/ determinant;
        }
    }
		printf("\n");

    for (int i = 0; i < empty_intialiser_for_rows_1; i++){
        for (int j = 0; j < empty_intialiser_for_columns_1; j++){
            printf("%lf ", resultMatrix[i][j]);
        }
        printf("\n");
    }
    free(resultMatrix);
}

int main(void){
    option_repeat();

    return 0;
}