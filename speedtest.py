import ctypes
import os
import platform
import csv
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from datetime import datetime

# Define the result structure to match the C struct
class BenchmarkResults(ctypes.Structure):
    _fields_ = [
        ("int_add", ctypes.c_double),
        ("int_sub", ctypes.c_double),
        ("int_mul", ctypes.c_double),
        ("int_div", ctypes.c_double),
        ("float_add", ctypes.c_double),
        ("float_sub", ctypes.c_double),
        ("float_mul", ctypes.c_double),
        ("float_div", ctypes.c_double),
        ("sin_func", ctypes.c_double),
        ("cos_func", ctypes.c_double),
        ("sqrt_func", ctypes.c_double),
        ("log_func", ctypes.c_double),
        ("exp_func", ctypes.c_double),
    ]

def load_benchmark_library():
    """Load the appropriate benchmark library based on platform."""
    if platform.system() == 'Windows':
        lib_path = os.path.join(os.path.dirname(__file__), 'libbenchmark.dll')
        lib = ctypes.CDLL(lib_path)
    else:  # Linux, Mac
        lib_path = os.path.join(os.path.dirname(__file__), 'libbenchmark.so')
        lib = ctypes.CDLL(lib_path)
    
    # Define the return type for the function
    lib.run_benchmark.restype = BenchmarkResults
    lib.run_benchmark.argtypes = [ctypes.c_long]
    
    return lib

def run_benchmarks(iterations_list):
    """Run benchmarks for each iteration count and return results."""
    lib = load_benchmark_library()
    results = []
    
    for iterations in iterations_list:
        print(f"\nRunning benchmark with {iterations:,} iterations...")
        benchmark_result = lib.run_benchmark(iterations)
        
        # Convert C struct to dictionary
        result_dict = {
            'iterations': iterations,
            'int_add': benchmark_result.int_add,
            'int_sub': benchmark_result.int_sub,
            'int_mul': benchmark_result.int_mul,
            'int_div': benchmark_result.int_div,
            'float_add': benchmark_result.float_add,
            'float_sub': benchmark_result.float_sub,
            'float_mul': benchmark_result.float_mul,
            'float_div': benchmark_result.float_div,
            'sin_func': benchmark_result.sin_func,
            'cos_func': benchmark_result.cos_func,
            'sqrt_func': benchmark_result.sqrt_func,
            'log_func': benchmark_result.log_func,
            'exp_func': benchmark_result.exp_func
        }
        
        results.append(result_dict)
    
    return results

def save_to_csv(results, filename=None):
    """Save benchmark results to CSV file."""
    if filename is None:
        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        filename = f"benchmark_results_{timestamp}.csv"
    
    with open(filename, 'w', newline='') as csvfile:
        fieldnames = results[0].keys()
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
        
        writer.writeheader()
        for result in results:
            writer.writerow(result)
    
    print(f"Results saved to {filename}")
    return filename

def create_visualizations(results_file):
    """Create visualizations from benchmark results."""
    # Load data from CSV
    df = pd.read_csv(results_file)
    
    # Set up plots
    plt.figure(figsize=(15, 10))
    
    # Create iteration groups
    operation_groups = {
        'Integer Operations': ['int_add', 'int_sub', 'int_mul', 'int_div'],
        'Floating Point Operations': ['float_add', 'float_sub', 'float_mul', 'float_div'],
        'Math Functions': ['sin_func', 'cos_func', 'sqrt_func', 'log_func', 'exp_func']
    }
    
    # Plot each group
    for i, (group_name, operations) in enumerate(operation_groups.items()):
        plt.subplot(3, 1, i+1)
        
        for op in operations:
            plt.plot(df['iterations'], df[op], marker='o', label=op)
        
        plt.title(f'{group_name} Performance')
        plt.xlabel('Iterations')
        plt.ylabel('Time (seconds)')
        plt.xscale('log')  # Use log scale for iterations
        plt.grid(True, linestyle='--', alpha=0.7)
        plt.legend()
    
    plt.tight_layout()
    
    # Save plot
    plot_file = results_file.replace('.csv', '.png')
    plt.savefig(plot_file)
    plt.close()
    
    print(f"Visualization saved to {plot_file}")
    
    # Create normalized plot (time per iteration)
    plt.figure(figsize=(15, 10))
    
    for i, (group_name, operations) in enumerate(operation_groups.items()):
        plt.subplot(3, 1, i+1)
        
        for op in operations:
            # Calculate time per iteration
            normalized = df[op] / df['iterations']
            plt.plot(df['iterations'], normalized, marker='o', label=op)
        
        plt.title(f'{group_name} Performance (normalized per iteration)')
        plt.xlabel('Total Iterations')
        plt.ylabel('Time per iteration (seconds)')
        plt.xscale('log')
        plt.yscale('log')  # Log scale helps see small differences
        plt.grid(True, linestyle='--', alpha=0.7)
        plt.legend()
    
    plt.tight_layout()
    
    # Save normalized plot
    norm_plot_file = results_file.replace('.csv', '_normalized.png')
    plt.savefig(norm_plot_file)
    plt.close()
    
    print(f"Normalized visualization saved to {norm_plot_file}")

def main():
    # Define iterations to test (powers of 10)
    iterations_list = [10**i for i in range(5, 9)]  # 10^5 to 10^8
    
    # Run benchmarks
    results = run_benchmarks(iterations_list)
    
    # Save results to CSV
    csv_file = save_to_csv(results)
    
    # Create visualizations
    create_visualizations(csv_file)

if __name__ == "__main__":
    main()