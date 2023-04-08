import time
import numpy as np
from concurrent.futures import ThreadPoolExecutor


def bruteforce(A, B):

    # Initialize the result matrix with zeros
    result = [[0 for _ in range(A.shape[0])] for _ in range(A.shape[0])]

    # Perform matrix multiplication using nested for loops
    for i in range(A.shape[0]):
        for j in range(A.shape[0]):
            for k in range(A.shape[0]):
                result[i][j] += A[i][k] * B[k][j]

    return result


def strassen(A, B):

    # Base case
    if A.shape[0] == 1:
        return A[0][0] * B[0][0]
        
    # Lower bound of n/2
    n = A.shape[0] // 2

    # Divide into sub matrices
    A00 = A[:n, :n]
    A01 = A[:n, n:]
    A10 = A[n:, :n]
    A11 = A[n:, n:]
    B00 = B[:n, :n]
    B01 = B[:n, n:]
    B10 = B[n:, :n]
    B11 = B[n:, n:]

    # Get variables M1 to M7 
    M1 = strassen(A00 + A11, B00 + B11)
    M2 = strassen(A10 + A11, B00)
    M3 = strassen(A00, B01 - B11)
    M4 = strassen(A11, B10 - B00)
    M5 = strassen(A00 + A01, B11)
    M6 = strassen(A10 - A00, B00 + B01)
    M7 = strassen(A01 - A11, B10 + B11)

    # Plug in M1 to M7 to get sub matrices of C
    C00 = M1 + M4 - M5 + M7
    C01 = M3 + M5
    C10 = M2 + M4
    C11 = M1 - M2 + M3 + M6

    # Combine the sub matrices into the return result
    C = np.zeros((A.shape[0], A.shape[0]), dtype=np.int64)
    C[:n, :n] = C00
    C[:n, n:] = C01
    C[n:, :n] = C10
    C[n:, n:] = C11

    return C

def combinedAlgorithms(A, B, z: int):
    # Base case
    if int(A.shape[0]) == int(z):
        return bruteforce(A, B)
    
    # Lower bound of n/2
    n = A.shape[0] // 2

    # Divide into sub matrices
    A00 = A[:n, :n]
    A01 = A[:n, n:]
    A10 = A[n:, :n]
    A11 = A[n:, n:]
    B00 = B[:n, :n]
    B01 = B[:n, n:]
    B10 = B[n:, :n]
    B11 = B[n:, n:]

    # Get variables M1 to M7 
    M1 = strassen(A00 + A11, B00 + B11)
    M2 = strassen(A10 + A11, B00)
    M3 = strassen(A00, B01 - B11)
    M4 = strassen(A11, B10 - B00)
    M5 = strassen(A00 + A01, B11)
    M6 = strassen(A10 - A00, B00 + B01)
    M7 = strassen(A01 - A11, B10 + B11)

    # Plug in M1 to M7 to get sub matrices of C
    C00 = M1 + M4 - M5 + M7
    C01 = M3 + M5
    C10 = M2 + M4
    C11 = M1 - M2 + M3 + M6

    # Combine the sub matrices into the return result
    C = np.zeros((A.shape[0], A.shape[0]), dtype=np.int64)
    C[:n, :n] = C00
    C[:n, n:] = C01
    C[n:, :n] = C10
    C[n:, n:] = C11

    return C

def strassenv2(A, B):
    """ Testing purposes.

    Args:
        A:
        B:
        n:

    Returns:
        The product of matrices A and B.
    """

    # Base case
    if A.shape[0] == 1:
        return A[0][0] * B[0][0]

    n = A.shape[0] // 2        

    # Combine the sub matrices into C
    C = np.zeros((A.shape[0], A.shape[0]), dtype=np.int64)
    C[:n, :n] = (strassenv2(A[:n, :n] + A[n:, n:], B[:n, :n] + B[n:, n:]) + strassenv2(A[n:, n:], B[n:, :n] - B[:n, :n]) - strassenv2(A[:n, :n] + A[:n, n:], B[n:, n:]) + strassenv2((A[:n, n:] - A[n:, n:]), (B[n:, :n] + B[n:, n:])))
    C[:n, n:] = (strassenv2(A[:n, :n], B[:n, n:] - B[n:, n:]) + strassenv2(A[:n, :n] + A[:n, n:], B[n:, n:]))
    C[n:, :n] = (strassenv2(A[n:, :n] + A[n:, n:], B[:n, :n]) + strassenv2(A[n:, n:], B[n:, :n] - B[:n, :n]))
    C[n:, n:] = (strassenv2(A[:n, :n] + A[n:, n:], B[:n, :n] + B[n:, n:]) - strassenv2(A[n:, :n] + A[n:, n:], B[:n, :n]) + strassenv2(A[:n, :n], B[:n, n:] - B[n:, n:]) + strassenv2(A[n:, :n] - A[:n, :n], B[:n, :n] + B[:n, n:]))

    return C


def strassenv3(A, B, executor=None):
    """ Testing purposes.

    Args:
        A:
        B:
        n:

    Returns:
        The product of matrices A and B.
    """
    if A.shape[0] == 1:
        return A[0][0] * B[0][0]

    C = np.zeros((A.shape[0], A.shape[0]), dtype=np.int64)

    if executor is None:
        with ThreadPoolExecutor(max_workers=8) as executor:
            return strassenv3(A, B, executor)

    n = A.shape[0] // 2

    futures = [
        executor.submit(strassenv3, A[:n, :n] + A[n:, n:], B[:n, :n] + B[n:, n:]),
        executor.submit(strassenv3, A[n:, n:], B[n:, :n] - B[:n, :n]),
        executor.submit(strassenv3, A[:n, :n] + A[:n, n:], B[n:, n:]),
        executor.submit(strassenv3, A[:n, n:] - A[n:, n:], B[n:, :n] + B[n:, n:]),
        executor.submit(strassenv3, A[:n, :n], B[:n, n:] - B[n:, n:]),
        executor.submit(strassenv3, A[:n, :n] + A[:n, n:], B[n:, n:]),
        executor.submit(strassenv3, A[n:, :n] + A[n:, n:], B[:n, :n]),
        executor.submit(strassenv3, A[n:, n:], B[n:, :n] - B[:n, :n]),
        executor.submit(strassenv3, A[:n, :n] + A[n:, n:], B[:n, :n] + B[n:, n:]),
        executor.submit(strassenv3, A[n:, :n] + A[n:, n:], B[:n, :n]),
        executor.submit(strassenv3, A[:n, :n], B[:n, n:] - B[n:, n:]),
        executor.submit(strassenv3, A[n:, :n] - A[:n, :n], B[:n, :n] + B[:n, n:])
        ]

    results = [f.result() for f in futures]

    C[:A.shape[0]//2, :A.shape[0]//2] = results[0] + results[1] - results[2] + results[3]
    C[:A.shape[0]//2, A.shape[0]//2:] = results[4] + results[5]
    C[A.shape[0]//2:, :A.shape[0]//2] = results[6] + results[7]
    C[A.shape[0]//2:, A.shape[0]//2:] = results[8] - results[9] + results[10] + results[11]
    
    return C











def run_algorithms(choice: str):

    while True:
        x = input("Enter an integer for 2^n matrices: ")
        try:
            x = int(x)
            break
        except ValueError:
            print("Invalid input. Please enter a valid integer.")

    matrix1 = np.random.randint(0, 10, size=(2**x, 2**x), dtype=np.int64)
    matrix2 = np.random.randint(0, 10, size=(2**x, 2**x), dtype=np.int64)

   
    if choice == "1":
        print("Timer started...")
        start_time0 = time.time()
        result0 = bruteforce(matrix1, matrix2)
        end_time0 = time.time()
        
        elapsed_time0 = end_time0 - start_time0

        print("\n")
        print("Time for BruteForce:", elapsed_time0)
        print("\n")
    elif choice == "2":
        print("Timer started...")
        start_time1 = time.time()
        result1 = strassen(matrix1, matrix2)
        end_time1 = time.time()
        
        elapsed_time1 = end_time1 - start_time1

        print("\n")
        print("Time for Strassen:", elapsed_time1)
        print("\n")
    elif choice == "3":
        
        while True:
            n = input("Enter an integer for 2^n for the brute + Strass algorithm: ")
            try:
                n = int(n)
                break
            except ValueError:
                print("Invalid input. Please enter a valid integer.")
        

        print("Timer started...")
        start_time2 = time.time()
        result0 = combinedAlgorithms(matrix1, matrix2, 2**n)
        end_time2 = time.time()

        elapsed_time2 = end_time2 - start_time2

        print("\n")
        print("Time for Brute + Strass (n=%s): %d", n, elapsed_time2)
        print("\n")
    if choice == "4":
        
        while True:
            n = input("Enter an integer for 2^n for the brute + Strass algorithm: ")
            try:
                n = int(n)
                break
            except ValueError:
                print("Invalid input. Please enter a valid integer.")
        
        start_time0 = time.time()
        result0 = bruteforce(matrix1, matrix2)
        end_time0 = time.time()
        elapsed_time0 = end_time0 - start_time0
        print("\n")
        print("Time for BruteForce:", elapsed_time0)
        
        start_time1 = time.time()
        result1 = strassen(matrix1, matrix2)
        end_time1 = time.time()
        elapsed_time1 = end_time1 - start_time1
        print("\n")
        print("Time for Strassen:", elapsed_time1)
        
        start_time2 = time.time()
        result2 = combinedAlgorithms(matrix1, matrix2, 2**n)
        end_time2 = time.time()
        elapsed_time2 = end_time2 - start_time2
        print("\n")
        print("Time for Brute + Strass: ", elapsed_time2)
        print("\n")

        if np.array_equal(result0, result1) and np.array_equal(result1, result2):
            print("All arrays are equal! Success!")
