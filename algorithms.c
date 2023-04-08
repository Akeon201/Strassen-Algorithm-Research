#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>

//Author: Kenyon Leblanc

void add_matrices(int **A, int **B, int **result, int actual_matrix_n);
void subtract_matrices(int **A, int **B, int **result, int actual_matrix_n);
void strassen(int **A, int **B, int **C, int actual_matrix_n);
void strassenv2(int **A, int **B, int **C, int actual_matrix_n, int actual_strassv2_num);
void generate_random_matrix(int **matrix, int actual_matrix_n);
void bruteforce(int **A, int **B, int **C, int actual_matrix_n);
void run_bruteforce(int **A, int **B, int **C, int actual_matrix_n);
void run_strassen(int **A, int **B, int **C, int actual_matrix_n);
void run_strassenv2(int **A, int **B, int **C, int actual_matrix_n, int actual_strassv2_num);
void run_all(int **A, int **B, int **C, int actual_matrix_n, int actual_strassv2_num);
void initialize_matrices(int ***A, int ***B, int ***C, int actual_matrix_n);
void free_matrices(int **A, int **B, int **C, int actual_matrix_n);
void print_matrices(int **matrix1, int **matrix2, int actual_matrix_n);
void print_matrix(int **matrix, int actual_matrix_n);
void write_matrices_to_file(char *filename, int **matrix1, int **matrix2, int actual_matrix_n, int matrix_num, int strassenv2_n);
void write_matrix_to_file(char *filename, int **matrix, int actual_matrix_n, int matrix_num, int strassenv2_n);
void write_result_to_file(char *filename, char *alg1_name, double result1_time);
void write_results_to_file(char *filename, char *alg1_name, double result1_time, char *alg2_name, double result2_time, char *alg3_name, double result3_time);
int ***read_matrices_from_csv(const char *filename);
void input_initialize_matrix(int ***C, int input_actual_matrix_n);
void next_line(FILE *fp);

char print_matrices_toggle = 'y';
clock_t start_time1;
clock_t end_time1;
double elapsed_time1;
clock_t start_time2;
clock_t end_time2;
double elapsed_time2;
clock_t start_time3;
clock_t end_time3;
double elapsed_time3;
int input_actual_matrix_n;
int input_matrix_n; 
int input_num_matrices;
int matrice_increment_csv = 1;
int matrix_increment_csv = 1;


// If input from command line is only size 1, then interactive mode.
// Else read csv file as input.
int main(int argc, char **argv) {

    if(argc == 1) {

        while(1) {
            int choice;
            char filename[100];
            matrice_increment_csv = 1;
            matrix_increment_csv = 1;

            printf("\n\nEnter your choice:\n");
            printf("1. Brute Force Algorithm\n");
            printf("2. Strassen Algorithm\n");
            printf("3. Strassenv2 Algorithms\n");
            printf("4. Run All\n");
            printf("5. Exit\n");
            printf("\ninput: ");
            scanf("%d", &choice);
            printf("\n");

            if (choice != 5) {
                printf("Print matrices to console? y/n: ");
                scanf("%c", &print_matrices_toggle);
                scanf("%c", &print_matrices_toggle);
                print_matrices_toggle = tolower(print_matrices_toggle);
                printf("Please enter a filename (exclude '.csv'): ");
                scanf("%s", &filename);
            }

            // Test the strassen function with sample matrices
            int **A, **B, **C;

            if (choice == 1) {
                int matrix_n;
                printf("Enter matrix size (2^n): ");
                scanf("%d", &matrix_n);
                int actual_matrix_n = 1 << matrix_n;  

                int num_matrices;
                printf("Enter the amount of matrices to test: ");
                scanf("%d", &num_matrices);
                for(int i = 0; i < num_matrices; i++) {
                    initialize_matrices(&A, &B, &C, actual_matrix_n);   

                    printf("\nTest %d", i+1);

                    print_matrices(A, B, actual_matrix_n); 

                    run_bruteforce(A, B, C, actual_matrix_n);

                    print_matrix(C, actual_matrix_n);

                    printf("\nTime for BruteForce: %lf\n", elapsed_time1);

                    write_matrices_to_file(filename, A, B, actual_matrix_n, num_matrices, 0);
                    write_matrix_to_file(filename, C, actual_matrix_n, num_matrices, 0);
                    write_result_to_file(filename, "Bruteforce", elapsed_time1);

                    free_matrices(A, B, C, actual_matrix_n);
                }
            }
            else if (choice == 2) {
                int matrix_n;
                printf("Enter matrix size (2^n): ");
                scanf("%d", &matrix_n);
                int actual_matrix_n = 1 << matrix_n;   

                int num_matrices;
                printf("Enter the amount of matrices to test: ");
                scanf("%d", &num_matrices);
                for(int i = 0; i < num_matrices; i++) {
                    initialize_matrices(&A, &B, &C, actual_matrix_n);

                    printf("\nTest %d", i+1);

                    print_matrices(A, B, actual_matrix_n);

                    run_strassen(A, B, C, actual_matrix_n);

                    print_matrix(C, actual_matrix_n);

                    printf("\nTime for Strassen:   %lf\n", elapsed_time2);

                    write_matrices_to_file(filename, A, B, actual_matrix_n, num_matrices, 0);
                    write_matrix_to_file(filename, C, actual_matrix_n, num_matrices, 0);
                    write_result_to_file(filename, "Strassen", elapsed_time2);

                    free_matrices(A, B, C, actual_matrix_n);
                }
            }    
            else if (choice == 3) {
                int matrix_n;
                printf("Enter matrix size (2^n): ");
                scanf("%d", &matrix_n);
                int actual_matrix_n = 1 << matrix_n;   

                int actual_strassv2_num;
                int strassv2_n;
                printf("Enter an integer for strassenv2 cutoff: ");
                scanf("%d", &strassv2_n);
                actual_strassv2_num = 1 << strassv2_n;

                int num_matrices;
                printf("Enter the amount of matrices to test: ");
                scanf("%d", &num_matrices);
                for(int i = 0; i < num_matrices; i++) {
                    initialize_matrices(&A, &B, &C, actual_matrix_n);
                    
                    printf("\nTest %d", i+1);

                    print_matrices(A, B, actual_matrix_n);

                    run_strassenv2(A, B, C, actual_matrix_n, actual_strassv2_num);

                    print_matrix(C, actual_matrix_n);

                    printf("\nTime for Strassenv2: %lf\n", elapsed_time3);

                    write_matrices_to_file(filename, A, B, actual_matrix_n, num_matrices, actual_strassv2_num);
                    write_matrix_to_file(filename, C, actual_matrix_n, num_matrices, actual_strassv2_num);
                    write_result_to_file(filename, "Strassenv2", elapsed_time3);

                    free_matrices(A, B, C, actual_matrix_n);
                }
            }    
            else if (choice == 4) {
                int matrix_n;
                printf("Enter matrix size (2^n): ");
                scanf("%d", &matrix_n);
                int actual_matrix_n = 1 << matrix_n; 

                int actual_strassv2_num;
                int strassv2_n;
                printf("Enter an integer for strassenv2 cutoff: ");
                scanf("%d", &strassv2_n);
                actual_strassv2_num = 1 << strassv2_n;

                int num_matrices;
                printf("Enter the amount of matrices to test: ");
                scanf("%d", &num_matrices);
                for(int i = 0; i < num_matrices; i++) {
                    
                    initialize_matrices(&A, &B, &C, actual_matrix_n);

                    printf("\nTest %d", i+1);
                    print_matrices(A, B, actual_matrix_n);

                    run_bruteforce(A, B, C, actual_matrix_n);
                    print_matrix(C, actual_matrix_n);
                    printf("\nTime for BruteForce: %lf", elapsed_time1);

                    run_strassen(A, B, C, actual_matrix_n);
                    print_matrix(C, actual_matrix_n);
                    printf("\nTime for Strassen:   %lf", elapsed_time2);

                    run_strassenv2(A, B, C, actual_matrix_n, actual_strassv2_num);
                    print_matrix(C, actual_matrix_n);
                    printf("\nTime for Strassenv2: %lf\n", elapsed_time3);

                    write_matrices_to_file(filename, A, B, actual_matrix_n, num_matrices, actual_strassv2_num);
                    write_matrix_to_file(filename, C, actual_matrix_n, num_matrices, actual_strassv2_num);
                    write_results_to_file(filename, "Bruteforce", elapsed_time1, "Strassen", elapsed_time2, "Strassenv2", elapsed_time3);

                    free_matrices(A, B, C, actual_matrix_n);
                }
            }
            else if (choice == 5) {
                printf("Exiting...\n");
                exit(0);
            }    

        }
    } else {

        int ***arr = read_matrices_from_csv(argv[1]);

        int **C;
        input_initialize_matrix(&C, input_actual_matrix_n);
        int actual_strassv2_num;
        int strassv2_n;
        printf("Enter an integer for strassenv2 cutoff: ");
        scanf("%d", &strassv2_n);
        actual_strassv2_num = 1 << strassv2_n;

        if(input_num_matrices == 2) { 
            char filename[100];
            printf("Print matrices to console? y/n: ");
            scanf("%c", &print_matrices_toggle);
            scanf("%c", &print_matrices_toggle);
            print_matrices_toggle = tolower(print_matrices_toggle);
            printf("Please enter a filename (exclude '.csv'): ");
            scanf("%s", &filename);

            printf("\nTest %d", 1);
            
            print_matrices(arr[0], arr[1], input_actual_matrix_n);

            run_bruteforce(arr[0], arr[1], C, input_actual_matrix_n);
            print_matrix(C, input_actual_matrix_n);
            printf("\nTime for BruteForce: %lf", elapsed_time1);

            run_strassen(arr[0], arr[1], C, input_actual_matrix_n);
            print_matrix(C, input_actual_matrix_n);
            printf("\nTime for Strassen:   %lf", elapsed_time2);

            run_strassenv2(arr[0], arr[1], C, input_actual_matrix_n, actual_strassv2_num);
            print_matrix(C, input_actual_matrix_n);
            printf("\nTime for Strassenv2: %lf\n", elapsed_time3);

            write_matrix_to_file(filename, C, input_actual_matrix_n, input_num_matrices, actual_strassv2_num);
            write_results_to_file(filename, "Bruteforce", elapsed_time1, "Strassen", elapsed_time2, "Strassenv2", elapsed_time3);

        } else {
                char filename[100];
                printf("Print matrices to console? y/n: ");
                scanf("%c", &print_matrices_toggle);
                scanf("%c", &print_matrices_toggle);
                print_matrices_toggle = tolower(print_matrices_toggle);
                printf("Please enter a filename (exclude '.csv'): ");
                scanf("%s", &filename);
                int x = 1;
                for(int i = 1; i < input_num_matrices; i+=2) {

                    printf("\nTest %d", x++);

                    print_matrices(arr[i-1], arr[i], input_actual_matrix_n);

                    run_bruteforce(arr[i-1], arr[i], C, input_actual_matrix_n);
                    print_matrix(C, input_actual_matrix_n);
                    printf("\nTime for BruteForce: %lf", elapsed_time1);

                    run_strassen(arr[i-1], arr[i], C, input_actual_matrix_n);
                    print_matrix(C, input_actual_matrix_n);
                    printf("\nTime for Strassen:   %lf", elapsed_time2);

                    run_strassenv2(arr[i-1], arr[i], C, input_actual_matrix_n, actual_strassv2_num);
                    print_matrix(C, input_actual_matrix_n);
                    printf("\nTime for Strassenv2: %lf\n", elapsed_time3);

                    write_matrix_to_file(filename, C, input_actual_matrix_n, input_num_matrices, actual_strassv2_num);
                    write_results_to_file(filename, "Bruteforce", elapsed_time1, "Strassen", elapsed_time2, "Strassenv2", elapsed_time3);
                }
        }


    }
    
}

// Write matrices to file
void write_matrices_to_file(char *filename, int **matrix1, int **matrix2, int actual_matrix_n, int matrix_num, int strassenv2_n) {
    char temp[100] = { "" };
    strcat(temp, filename);
    strcat(temp, "_matrix.csv");
    FILE *file = fopen(temp, "a+");
    if (file == NULL) {
        printf("Error opening file: %s\n", temp);
        return;
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    if (filesize == 0) {
        fprintf(file, "strassenv2_cutoff,size,pairs");
        for(int i = 0; i < actual_matrix_n-2; i++) {
            fprintf(file, ",");
        }
        fprintf(file, "\n");
        fprintf(file, "%d,%d,%d", strassenv2_n, actual_matrix_n, matrix_num);
        for(int i = 0; i < actual_matrix_n-2; i++) {
            fprintf(file, ",");
        }        
        fprintf(file, "\n");   
    }

    for (int i = 0; i < actual_matrix_n; i++) {
        for (int j = 0; j < actual_matrix_n; j++) {
            fprintf(file, "%d,", matrix1[i][j]);
        }
        fprintf(file, "\n"); 
    }
    for(int i = 0; i < actual_matrix_n; i++) {
        fprintf(file, ",");
    }
    fprintf(file, "\n");

    for (int i = 0; i < actual_matrix_n; i++) {
        for (int j = 0; j < actual_matrix_n; j++) {
            fprintf(file, "%d,", matrix2[i][j]);
        }
        fprintf(file, "\n"); 
    }
 
    fprintf(file, "~%d", matrice_increment_csv++);
    for(int i = 0; i < actual_matrix_n; i++) {
        fprintf(file, ",");
    }
    fprintf(file, "\n");   

    fclose(file);
}

// Write a matrix to file
void write_matrix_to_file(char *filename, int **matrix, int actual_matrix_n, int matrix_num, int strassenv2_n) {
    char temp[100] = { "" };
    strcat(temp, filename);
    strcat(temp, "_C.csv");
    FILE *file = fopen(temp, "a+");
    if (file == NULL) {
        printf("Error opening file: %s\n", temp);
        return;
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    if (filesize == 0) {
        fprintf(file, "strassenv2_cutoff,size,pairs");
        for(int i = 0; i < actual_matrix_n-2; i++) {
            fprintf(file, ",");
        }
        fprintf(file, "\n");
        fprintf(file, "%d,%d,%d", strassenv2_n, actual_matrix_n, matrix_num);
        for(int i = 0; i < actual_matrix_n-2; i++) {
            fprintf(file, ",");
        }        
        fprintf(file, "\n");
        for(int i = 0; i < actual_matrix_n; i++) {
        fprintf(file, ",");
        }
        fprintf(file, "\n");    
    }

    for (int i = 0; i < actual_matrix_n; i++) {
        for (int j = 0; j < actual_matrix_n; j++) {
            fprintf(file, "%d,", matrix[i][j]);
        }
        fprintf(file, "\n"); 
    }
 
    fprintf(file, "~%d", matrix_increment_csv++);
    for(int i = 0; i < actual_matrix_n; i++) {
        fprintf(file, ",");
    }
    fprintf(file, "\n");   

    fclose(file);
}

// Write results of single algorithm to file
void write_result_to_file(char *filename, char *alg1_name, double result1_time) {
    char temp[100] = { "" };
    strcat(temp, filename);
    strcat(temp, "_result.csv");
    FILE *file = fopen(temp, "a+");
    if (file == NULL) {
        printf("Error opening file: %s\n", temp);
        return;
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    if (filesize == 0) {
        fprintf(file, "%s Time (Seconds),", alg1_name);
        fprintf(file, "\n");
    }

    for (int i = 0; i < 1; i++) {
        fprintf(file, "%f,", result1_time);
    }
    fprintf(file, "\n");   

    fclose(file);
}

// Write algorithms and times to a file
void write_results_to_file(char *filename, char *alg1_name, double result1_time, char *alg2_name, double result2_time, char *alg3_name, double result3_time) {
    char temp[100] = { "" };
    strcat(temp, filename);
    strcat(temp, "_result.csv");
    FILE *file = fopen(temp, "a+");
    if (file == NULL) {
        printf("Error opening file: %s\n", temp);
        return;
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    if (filesize == 0) {
        fprintf(file, "%s Time (Seconds),%s Time (Seconds),%s Time (Seconds),", alg1_name, alg2_name, alg3_name);
        fprintf(file, "\n");
    }

    for (int i = 0; i < 1; i++) {
        fprintf(file, "%f,%f,%f,", result1_time, result2_time, result3_time);
    }
    fprintf(file, "\n");   

    fclose(file);
}

// Print matrices
void print_matrices(int **matrix1, int **matrix2, int actual_matrix_n) {
    if (print_matrices_toggle == 'y') {
        printf("\nA:\n");
        for (int i = 0; i < actual_matrix_n; i++) {
            for (int j = 0; j < actual_matrix_n; j++) {
                printf("\t%d", matrix1[i][j]);
            }
            printf("\n");
        }

        printf("\nB:\n");
        for (int i = 0; i < actual_matrix_n; i++) {
            for (int j = 0; j < actual_matrix_n; j++) {
                printf("\t%d", matrix2[i][j]);
            }
            printf("\n");
        }    
    }     
} 

// Print a matrix
void print_matrix(int **matrix, int actual_matrix_n) {
    if (print_matrices_toggle == 'y') {
        printf("\n\nC:");
        for (int i = 0; i < actual_matrix_n; i++) {
            for (int j = 0; j < actual_matrix_n; j++) {
                printf("\t%d", matrix[i][j]);
            }
            printf("\n");
        }
    }
}

// Initialize matrices
void initialize_matrices(int ***A, int ***B, int ***C, int actual_matrix_n) {
    *A = malloc(actual_matrix_n * sizeof(int *));
    *B = malloc(actual_matrix_n * sizeof(int *));
    *C = malloc(actual_matrix_n * sizeof(int *));

    for (int i = 0; i < actual_matrix_n; i++) {
        (*A)[i] = malloc(actual_matrix_n * sizeof(int));
        (*B)[i] = malloc(actual_matrix_n * sizeof(int));
        (*C)[i] = malloc(actual_matrix_n * sizeof(int));
    }

    generate_random_matrix(*A, actual_matrix_n);
    generate_random_matrix(*B, actual_matrix_n);
    
}

// Initialize a matrix
void input_initialize_matrix(int ***C, int input_actual_matrix_n) {
    *C = (int **) malloc(input_actual_matrix_n * sizeof(int *));

    for (int i = 0; i < input_actual_matrix_n; i++) {
        (*C)[i] = (int *) malloc(input_actual_matrix_n * sizeof(int));
    }
    
}

// Free multiple matrices
void free_matrices(int **A, int **B, int **C, int actual_matrix_n) {

    for (int i = 0; i < actual_matrix_n; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }

    free(A);
    free(B);
    free(C);
}

// Add two matrices
void add_matrices(int **A, int **B, int **result, int actual_matrix_n) {
    for (int i = 0; i < actual_matrix_n; i++) {
        for (int j = 0; j < actual_matrix_n; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
}

// Subtract two matrices
void subtract_matrices(int **A, int **B, int **result, int actual_matrix_n) {
    for (int i = 0; i < actual_matrix_n; i++) {
        for (int j = 0; j < actual_matrix_n; j++) {
            result[i][j] = A[i][j] - B[i][j];
        }
    }
}

// Generate a random matrix
void generate_random_matrix(int **matrix, int actual_matrix_n) {
    for (int i = 0; i < actual_matrix_n; i++) {
        for (int j = 0; j < actual_matrix_n; j++) {
            matrix[i][j] = rand() % 10;
        }
    }
}

// Bruteforce algorithm
void bruteforce(int **A, int **B, int **C, int actual_matrix_n) {
    for (int i = 0; i < actual_matrix_n; i++) {
        for (int j = 0; j < actual_matrix_n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < actual_matrix_n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Run bruteforce algorithm
void run_bruteforce(int **A, int **B, int **C, int actual_matrix_n) {
    start_time1 = clock();
    bruteforce(A, B, C, actual_matrix_n);
    end_time1 = clock();
    elapsed_time1 = ((double) (end_time1 - start_time1)) / CLOCKS_PER_SEC;
}

//run strassen algorithm
void run_strassen(int **A, int **B, int **C, int actual_matrix_n) {
    start_time2 = clock();
    strassen(A, B, C, actual_matrix_n);
    end_time2 = clock();
    elapsed_time2 = ((double) (end_time2 - start_time2)) / CLOCKS_PER_SEC;
}

// Run combined algorithm
void run_strassenv2(int **A, int **B, int **C, int actual_matrix_n, int actual_strassv2_num) {
    if (actual_strassv2_num > actual_matrix_n) { actual_strassv2_num =  actual_matrix_n; }
    start_time3 = clock();
    strassenv2(A, B, C, actual_matrix_n, actual_strassv2_num);
    end_time3 = clock();
    elapsed_time3 = ((double) (end_time3 - start_time3)) / CLOCKS_PER_SEC;
}

// Run all algorithms
void run_all(int **A, int **B, int **C, int actual_matrix_n, int actual_strassv2_num) {
    start_time1 = clock();
    bruteforce(A, B, C, actual_matrix_n);
    end_time1 = clock();
    elapsed_time1 = ((double) (end_time1 - start_time1)) / CLOCKS_PER_SEC;
    printf("\nTime for BruteForce: %lf", elapsed_time1);

    start_time2 = clock();
    strassen(A, B, C, actual_matrix_n);
    end_time2 = clock();
    elapsed_time2 = ((double) (end_time2 - start_time2)) / CLOCKS_PER_SEC;
    printf("\nTime for Strassen: %lf", elapsed_time2);

    start_time3 = clock();
    strassenv2(A, B, C, actual_matrix_n, actual_strassv2_num);
    end_time3 = clock();
    elapsed_time3 = ((double) (end_time3 - start_time3)) / CLOCKS_PER_SEC;
    printf("\nTime for Strassenv2: %lf", elapsed_time3);

}

// Strassen Algorithm
void strassen(int **A, int **B, int **C, int actual_matrix_n) {
    if (actual_matrix_n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int half = actual_matrix_n / 2;

    // Allocate memory for submatrices
    int **A00 = malloc(half * sizeof(int *));
    int **A01 = malloc(half * sizeof(int *));
    int **A10 = malloc(half * sizeof(int *));
    int **A11 = malloc(half * sizeof(int *));
    int **B00 = malloc(half * sizeof(int *));
    int **B01 = malloc(half * sizeof(int *));
    int **B10 = malloc(half * sizeof(int *));
    int **B11 = malloc(half * sizeof(int *));
    int **C00 = malloc(half * sizeof(int *));
    int **C01 =malloc(half * sizeof(int *));
    int **C10 = malloc(half * sizeof(int *));
    int **C11 = malloc(half * sizeof(int *));
    int **M1 = malloc(half * sizeof(int *));
    int **M2 = malloc(half * sizeof(int *));
    int **M3 = malloc(half * sizeof(int *));
    int **M4 = malloc(half * sizeof(int *));
    int **M5 = malloc(half * sizeof(int *));
    int **M6 = malloc(half * sizeof(int *));
    int **M7 = malloc(half * sizeof(int *));
    int **temp1 = malloc(half * sizeof(int *));
    int **temp2 = malloc(half * sizeof(int *));

    for (int i = 0; i < half; i++) {
        A00[i] = malloc(half * sizeof(int));
        A01[i] = malloc(half * sizeof(int));
        A10[i] = malloc(half * sizeof(int));
        A11[i] = malloc(half * sizeof(int));
        B00[i] = malloc(half * sizeof(int));
        B01[i] = malloc(half * sizeof(int));
        B10[i] = malloc(half * sizeof(int));
        B11[i] = malloc(half * sizeof(int));
        C00[i] = malloc(half * sizeof(int));
        C01[i] = malloc(half * sizeof(int));
        C10[i] = malloc(half * sizeof(int));
        C11[i] = malloc(half * sizeof(int));
        M1[i] = malloc(half * sizeof(int));
        M2[i] = malloc(half * sizeof(int));
        M3[i] = malloc(half * sizeof(int));
        M4[i] = malloc(half * sizeof(int));
        M5[i] = malloc(half * sizeof(int));
        M6[i] = malloc(half * sizeof(int));
        M7[i] = malloc(half * sizeof(int));
        temp1[i] = malloc(half * sizeof(int));
        temp2[i] = malloc(half * sizeof(int));
    }

    // Divide input matrices into submatrices
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            A00[i][j] = A[i][j];
            A01[i][j] = A[i][j + half];
            A10[i][j] = A[i + half][j];
            A11[i][j] = A[i + half][j + half];
            B00[i][j] = B[i][j];
            B01[i][j] = B[i][j + half];
            B10[i][j] = B[i + half][j];
            B11[i][j] = B[i + half][j + half];
        }
    }

    // Calculate M1 to M7
    add_matrices(A00, A11, temp1, half);
    add_matrices(B00, B11, temp2, half);
    strassen(temp1, temp2, M1, half);

    add_matrices(A10, A11, temp1, half);
    strassen(temp1, B00, M2, half);

    subtract_matrices(B01, B11, temp1, half);
    strassen(A00, temp1, M3, half);

    subtract_matrices(B10, B00, temp1, half);
    strassen(A11, temp1, M4, half);

    add_matrices(A00, A01, temp1, half);
    strassen(temp1, B11, M5, half);

    subtract_matrices(A10, A00, temp1, half);
    add_matrices(B00, B01, temp2, half);
    strassen(temp1, temp2, M6, half);

    subtract_matrices(A01, A11, temp1, half);
    add_matrices(B10, B11, temp2, half);
    strassen(temp1, temp2, M7, half);

    // Calculate submatrices of C
    add_matrices(M1, M4, temp1, half);
    subtract_matrices(temp1, M5, temp2, half);
    add_matrices(temp2, M7, C00, half);

    add_matrices(M3, M5, C01, half);

    add_matrices(M2, M4, C10, half);

    subtract_matrices(M1, M2, temp1, half);
    add_matrices(temp1, M3, temp2, half);
    add_matrices(temp2, M6, C11, half);

    // Combine submatrices into result matrix C
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            C[i][j] = C00[i][j];
            C[i][j + half] = C01[i][j];
            C[i + half][j] = C10[i][j];
            C[i + half][j + half] = C11[i][j];
        }
    }

    // Free allocated memory
    for (int i = 0; i < half; i++) {
        free(A00[i]); 
        free(A01[i]); 
        free(A10[i]); 
        free(A11[i]);
        free(B00[i]); 
        free(B01[i]); 
        free(B10[i]); 
        free(B11[i]);
        free(C00[i]); 
        free(C01[i]); 
        free(C10[i]); 
        free(C11[i]);
        free(M1[i]); 
        free(M2[i]); 
        free(M3[i]); 
        free(M4[i]);
        free(M5[i]); 
        free(M6[i]); 
        free(M7[i]);
        free(temp1[i]); 
        free(temp2[i]);
    }

    free(A00); 
    free(A01); 
    free(A10); 
    free(A11);
    free(B00); 
    free(B01); 
    free(B10); 
    free(B11);
    free(C00); 
    free(C01); 
    free(C10); 
    free(C11);
    free(M1); 
    free(M2); 
    free(M3); 
    free(M4);
    free(M5); 
    free(M6); 
    free(M7);
    free(temp1); 
    free(temp2);
}

// Combined algorithm
void strassenv2(int **A, int **B, int **C, int actual_matrix_n, int actual_strassv2_num) {
    if (actual_matrix_n == actual_strassv2_num) {
        bruteforce(A, B, C, actual_strassv2_num);
        return;
    }

    int half = actual_matrix_n / 2;

    int **A00 = malloc(half * sizeof(int *));
    int **A01 = malloc(half * sizeof(int *));
    int **A10 = malloc(half * sizeof(int *));
    int **A11 = malloc(half * sizeof(int *));
    int **B00 = malloc(half * sizeof(int *));
    int **B01 = malloc(half * sizeof(int *));
    int **B10 = malloc(half * sizeof(int *));
    int **B11 = malloc(half * sizeof(int *));
    int **C00 = malloc(half * sizeof(int *));
    int **C01 = malloc(half * sizeof(int *));
    int **C10 = malloc(half * sizeof(int *));
    int **C11 = malloc(half * sizeof(int *));
    int **M1 = malloc(half * sizeof(int *));
    int **M2 = malloc(half * sizeof(int *));
    int **M3 = malloc(half * sizeof(int *));
    int **M4 = malloc(half * sizeof(int *));
    int **M5 = malloc(half * sizeof(int *));
    int **M6 = malloc(half * sizeof(int *));
    int **M7 = malloc(half * sizeof(int *));
    int **temp1 = malloc(half * sizeof(int *));
    int **temp2 = malloc(half * sizeof(int *));

    for (int i = 0; i < half; i++) {
        A00[i] = malloc(half * sizeof(int));
        A01[i] = malloc(half * sizeof(int));
        A10[i] = malloc(half * sizeof(int));
        A11[i] = malloc(half * sizeof(int));
        B00[i] = malloc(half * sizeof(int));
        B01[i] = malloc(half * sizeof(int));
        B10[i] = malloc(half * sizeof(int));
        B11[i] = malloc(half * sizeof(int));
        C00[i] = malloc(half * sizeof(int));
        C01[i] = malloc(half * sizeof(int));
        C10[i] = malloc(half * sizeof(int));
        C11[i] = malloc(half * sizeof(int));
        M1[i] = malloc(half * sizeof(int));
        M2[i] = malloc(half * sizeof(int));
        M3[i] = malloc(half * sizeof(int));
        M4[i] = malloc(half * sizeof(int));
        M5[i] = malloc(half * sizeof(int));
        M6[i] = malloc(half * sizeof(int));
        M7[i] = malloc(half * sizeof(int));
        temp1[i] = malloc(half * sizeof(int));
        temp2[i] = malloc(half * sizeof(int));
    }

    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            A00[i][j] = A[i][j];
            A01[i][j] = A[i][j + half];
            A10[i][j] = A[i + half][j];
            A11[i][j] = A[i + half][j + half];
            B00[i][j] = B[i][j];
            B01[i][j] = B[i][j + half];
            B10[i][j] = B[i + half][j];
            B11[i][j] = B[i + half][j + half];
        }
    }

    add_matrices(A00, A11, temp1, half);
    add_matrices(B00, B11, temp2, half);
    strassenv2(temp1, temp2, M1, half, actual_strassv2_num);

    add_matrices(A10, A11, temp1, half);
    strassenv2(temp1, B00, M2, half, actual_strassv2_num);

    subtract_matrices(B01, B11, temp1, half);
    strassenv2(A00, temp1, M3, half, actual_strassv2_num);

    subtract_matrices(B10, B00, temp1, half);
    strassenv2(A11, temp1, M4, half, actual_strassv2_num);

    add_matrices(A00, A01, temp1, half);
    strassenv2(temp1, B11, M5, half, actual_strassv2_num);

    subtract_matrices(A10, A00, temp1, half);
    add_matrices(B00, B01, temp2, half);
    strassenv2(temp1, temp2, M6, half, actual_strassv2_num);

    subtract_matrices(A01, A11, temp1, half);
    add_matrices(B10, B11, temp2, half);
    strassenv2(temp1, temp2, M7, half, actual_strassv2_num);

    add_matrices(M1, M4, temp1, half);
    subtract_matrices(temp1, M5, temp2, half);
    add_matrices(temp2, M7, C00, half);

    add_matrices(M3, M5, C01, half);

    add_matrices(M2, M4, C10, half);

    subtract_matrices(M1, M2, temp1, half);
    add_matrices(temp1, M3, temp2, half);
    add_matrices(temp2, M6, C11, half);

    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            C[i][j] = C00[i][j];
            C[i][j + half] = C01[i][j];
            C[i + half][j] = C10[i][j];
            C[i + half][j + half] = C11[i][j];
        }
    }

    for (int i = 0; i < half; i++) {
        free(A00[i]); 
        free(A01[i]); 
        free(A10[i]); 
        free(A11[i]);
        free(B00[i]); 
        free(B01[i]); 
        free(B10[i]); 
        free(B11[i]);
        free(C00[i]); 
        free(C01[i]); 
        free(C10[i]); 
        free(C11[i]);
        free(M1[i]); 
        free(M2[i]); 
        free(M3[i]); 
        free(M4[i]);
        free(M5[i]); 
        free(M6[i]); 
        free(M7[i]);
        free(temp1[i]); 
        free(temp2[i]);
    }

    free(A00); 
    free(A01); 
    free(A10); 
    free(A11);
    free(B00); 
    free(B01); 
    free(B10); 
    free(B11);
    free(C00); 
    free(C01); 
    free(C10); 
    free(C11);
    free(M1); 
    free(M2); 
    free(M3); 
    free(M4);
    free(M5); 
    free(M6); 
    free(M7);
    free(temp1); 
    free(temp2);
}

// Goto next line 
void next_line(FILE *fp) {
    while (1) {
    int c = fgetc(fp);
    if (c == '\n' || c == '\r' || c == EOF) {
        break; // found end of line or end of file
    }
}

}
int ***read_matrices_from_csv(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Cannot open the file.\n");
        exit(0);
    }

    next_line(file);

    fscanf(file, "%d%*c%d%*c%d", &input_matrix_n, &input_actual_matrix_n, &input_num_matrices);
    input_num_matrices *= 2;
    next_line(file);

    int ***arr = (int ***)malloc(input_num_matrices * sizeof(int **));
    for (int i = 0; i < input_num_matrices; i++) {
        arr[i] = (int **)malloc(input_actual_matrix_n * sizeof(int *));
        for (int j = 0; j < input_actual_matrix_n; j++) {
            arr[i][j] = (int *)malloc(input_actual_matrix_n * sizeof(int));
        }
    }
    
    int temp = 0;
    for (int k = 0; k < input_num_matrices; k++) {
        for (int i = 0; i < input_actual_matrix_n; i++) {
            for (int j = 0; j < input_actual_matrix_n; j++) {
                fscanf(file, "%d%*c", &arr[k][i][j]);
            }
            next_line(file);
        }
        next_line(file);
    }

    fclose(file);
    return arr;
}
