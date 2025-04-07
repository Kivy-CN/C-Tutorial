import ctypes
import os
import platform
import csv
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from datetime import datetime
import time
import sys
import matplotlib as mpl
from matplotlib.ticker import FuncFormatter

# Set a modern style for matplotlib
plt.style.use('ggplot')
mpl.rcParams['font.family'] = 'DejaVu Sans'
mpl.rcParams['font.size'] = 12
mpl.rcParams['axes.labelsize'] = 14
mpl.rcParams['axes.titlesize'] = 16
mpl.rcParams['xtick.labelsize'] = 12
mpl.rcParams['ytick.labelsize'] = 12
mpl.rcParams['legend.fontsize'] = 12

# Define a better color palette (colorblind-friendly)
COLORS = ['#1f77b4', '#ff7f0e', '#2ca02c', '#d62728', '#9467bd', 
          '#8c564b', '#e377c2', '#7f7f7f', '#bcbd22', '#17becf']

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
        # Try multiple possible DLL names
        possible_filenames = ['benchmark.dll', 'libbenchmark.dll']
        
        for filename in possible_filenames:
            # Try absolute path first
            lib_path = os.path.join(os.path.dirname(__file__), filename)
            try:
                lib = ctypes.CDLL(lib_path)
                print(f"✅ Successfully loaded library from: {lib_path}")
                break
            except Exception as e:
                print(f"❌ Failed to load {lib_path}: {e}")
                
                # Try current directory
                try:
                    lib = ctypes.CDLL(filename)
                    print(f"✅ Successfully loaded library from current directory: {filename}")
                    break
                except Exception as e2:
                    print(f"❌ Failed to load {filename} from current directory: {e2}")
        else:  # If all attempts fail
            print("⚠️ Could not load the benchmark library. Make sure it's compiled correctly.")
            print("💡 Try running: gcc -shared -o benchmark.dll -O2 \"运算速度测试.c\" -lm")
            sys.exit(1)
    else:  # Linux, Mac
        lib_path = os.path.join(os.path.dirname(__file__), 'libbenchmark.so')
        try:
            lib = ctypes.CDLL(lib_path)
            print(f"✅ Successfully loaded library from: {lib_path}")
        except Exception as e:
            print(f"❌ Error loading library: {e}")
            print("💡 Try running: gcc -shared -fPIC -o libbenchmark.so -O2 \"运算速度测试.c\" -lm")
            sys.exit(1)
    
    # Define the return type for the function
    lib.run_benchmark.restype = BenchmarkResults
    lib.run_benchmark.argtypes = [ctypes.c_long]
    
    return lib

def run_benchmarks(iterations_list, timeout=600):
    """
    Run benchmarks for each iteration count and return results.
    
    Args:
        iterations_list: List of iteration counts to test
        timeout: Maximum time in seconds to allow for each benchmark
    """
    lib = load_benchmark_library()
    results = []
    
    # Progress tracker
    total_tests = len(iterations_list)
    completed_tests = 0
    
    print("\n🚀 Starting benchmark suite with following iteration counts:")
    for i, count in enumerate(iterations_list):
        print(f"  {i+1}. {count:,}")
    
    for iterations in iterations_list:
        completed_tests += 1
        print(f"\n📊 Running benchmark [{completed_tests}/{total_tests}] with {iterations:,} iterations...")
        
        # Set a timeout for very large iteration counts
        start_time = time.time()
        try:
            benchmark_result = lib.run_benchmark(iterations)
            elapsed = time.time() - start_time
            
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
            print(f"✅ Completed in {elapsed:.2f} seconds")
            
            # If this benchmark took too long, skip larger iteration counts
            if elapsed > timeout / 2:
                remaining = [i for i in iterations_list if i > iterations]
                if remaining:
                    print(f"⚠️ Warning: Current test took {elapsed:.2f} seconds. Larger tests might timeout.")
                    skip_larger = input(f"Skip larger tests ({remaining})? (y/n): ")
                    if skip_larger.lower() == 'y':
                        print(f"⏩ Skipping remaining larger tests: {remaining}")
                        break
        
        except KeyboardInterrupt:
            print("\n🛑 Benchmark interrupted by user.")
            skip_larger = input("Skip larger iterations? (y/n): ")
            if skip_larger.lower() == 'y':
                break
            continue
            
        except Exception as e:
            print(f"❌ Error running benchmark with {iterations} iterations: {e}")
            continue
        
    return results

def save_to_csv(results, filename=None):
    """Save benchmark results to CSV file."""
    if not results:
        print("❌ No results to save.")
        return None
        
    if filename is None:
        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        filename = f"benchmark_results_{timestamp}.csv"
    
    with open(filename, 'w', newline='') as csvfile:
        fieldnames = results[0].keys()
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
        
        writer.writeheader()
        for result in results:
            writer.writerow(result)
    
    print(f"💾 Results saved to {filename}")
    return filename

# Helper function to format large numbers
def format_large_number(x, pos):
    if x >= 1e9:
        return f'{x/1e9:.0f}B'
    elif x >= 1e6:
        return f'{x/1e6:.0f}M'
    elif x >= 1e3:
        return f'{x/1e3:.0f}K'
    else:
        return f'{x:.0f}'

def create_visualizations(results_file):
    """Create enhanced visualizations from benchmark results."""
    print("\n🎨 Creating visualizations...")
    
    # Load data from CSV
    df = pd.read_csv(results_file)
    
    # Define operation groups with better naming for display
    operation_groups = {
        'Integer Operations': {
            'int_add': 'Integer Addition',
            'int_sub': 'Integer Subtraction', 
            'int_mul': 'Integer Multiplication', 
            'int_div': 'Integer Division'
        },
        'Floating Point Operations': {
            'float_add': 'Float Addition', 
            'float_sub': 'Float Subtraction', 
            'float_mul': 'Float Multiplication', 
            'float_div': 'Float Division'
        },
        'Math Functions': {
            'sin_func': 'Sine', 
            'cos_func': 'Cosine', 
            'sqrt_func': 'Square Root', 
            'log_func': 'Logarithm', 
            'exp_func': 'Exponential'
        }
    }
    
    # Create output directory for visualizations
    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    output_dir = f"benchmark_viz_{timestamp}"
    os.makedirs(output_dir, exist_ok=True)
    
    # ---- 1. STACKED AREA CHART ----
    # Shows how the composition of time changes with iteration count
    plt.figure(figsize=(14, 8))
    
    # Prepare data for stacking
    stack_data = df.set_index('iterations').copy()
    stack_cols = []
    labels = []
    
    # Collect data and labels for all operations
    for group_name, operations in operation_groups.items():
        for op_code, op_name in operations.items():
            stack_cols.append(op_code)
            labels.append(op_name)
    
    # Create the stacked area chart
    plt.stackplot(df['iterations'], [df[col] for col in stack_cols], 
                 labels=labels, alpha=0.8, colors=COLORS)
    
    plt.xscale('log')
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.xlabel('Number of Iterations')
    plt.ylabel('Execution Time (seconds)')
    plt.title('Composition of Execution Time by Operation Type', fontweight='bold')
    
    # Format x-axis with K, M, B suffixes
    plt.gca().xaxis.set_major_formatter(FuncFormatter(format_large_number))
    
    # Place legend outside the plot
    plt.legend(loc='center left', bbox_to_anchor=(1, 0.5))
    plt.tight_layout()
    
    stacked_file = os.path.join(output_dir, 'stacked_area_chart.png')
    plt.savefig(stacked_file, dpi=300, bbox_inches='tight')
    plt.close()
    print(f"📊 Stacked area chart saved to {stacked_file}")
    
    # ---- 2. RADAR CHART BY OPERATION GROUP ----
    # Shows the relative performance of different operations
    
    # Create a new figure for each iteration level
    for i, iteration in enumerate(df['iterations']):
        fig = plt.figure(figsize=(15, 5))
        
        for g_idx, (group_name, operations) in enumerate(operation_groups.items()):
            # Create a subplot for each operation group
            ax = fig.add_subplot(1, 3, g_idx+1, polar=True)
            
            # Get data for this group at this iteration level
            values = [df.iloc[i][op_code] for op_code in operations.keys()]
            op_names = list(operations.values())
            
            # Number of operations in this group
            N = len(values)
            
            # Compute angle for each operation
            angles = [n / float(N) * 2 * np.pi for n in range(N)]
            angles += angles[:1]  # Close the loop
            
            # Add the values (and repeat the first value to close the loop)
            values += values[:1]
            
            # Draw the radar chart
            ax.plot(angles, values, linewidth=2, label=group_name)
            ax.fill(angles, values, alpha=0.25)
            
            # Set the labels
            ax.set_xticks(angles[:-1])
            ax.set_xticklabels(op_names)
            
            # Configure the chart
            ax.set_title(group_name, size=14, fontweight='bold')
            plt.grid(True)
        
        plt.suptitle(f'Operation Performance at {format_large_number(iteration, 0)} Iterations', 
                   fontsize=16, fontweight='bold')
        plt.tight_layout()
        
        radar_file = os.path.join(output_dir, f'radar_chart_{iteration}.png')
        plt.savefig(radar_file, dpi=300, bbox_inches='tight')
        plt.close()
        print(f"📊 Radar chart for {format_large_number(iteration, 0)} iterations saved")
    
    # ---- 3. HORIZONTAL BAR CHART - COMPARATIVE VIEW ----
    # Shows operations ranked by execution time for each iteration count
    
    for i, iteration in enumerate(df['iterations']):
        plt.figure(figsize=(12, 10))
        
        # Get all operations and their times for this iteration
        ops = []
        values = []
        colors = []
        
        for g_idx, (group_name, operations) in enumerate(operation_groups.items()):
            for op_code, op_name in operations.items():
                ops.append(op_name)
                values.append(df.iloc[i][op_code])
                colors.append(COLORS[g_idx % len(COLORS)])
        
        # Sort by execution time
        sorted_indices = np.argsort(values)
        ops = [ops[i] for i in sorted_indices]
        values = [values[i] for i in sorted_indices]
        colors = [colors[i] for i in sorted_indices]
        
        # Create horizontal bars
        bars = plt.barh(ops, values, color=colors, alpha=0.8)
        
        # Add execution time labels at the end of each bar
        for bar in bars:
            width = bar.get_width()
            label_x_pos = width * 1.01
            plt.text(label_x_pos, bar.get_y() + bar.get_height()/2, f'{width:.4f}s',
                    va='center', fontsize=10)
        
        plt.xlabel('Execution Time (seconds)')
        plt.title(f'Operations Ranked by Execution Time at {format_large_number(iteration, 0)} Iterations', 
                 fontweight='bold')
        plt.grid(True, linestyle='--', alpha=0.7, axis='x')
        plt.tight_layout()
        
        ranking_file = os.path.join(output_dir, f'ranking_chart_{iteration}.png')
        plt.savefig(ranking_file, dpi=300)
        plt.close()
        print(f"📊 Ranking chart for {format_large_number(iteration, 0)} iterations saved")
    
    # ---- 4. BUBBLE CHART - RELATIVE PERFORMANCE ----
    # Shows relative performance using bubble size across iteration counts
    
    plt.figure(figsize=(15, 10))
    
    # Compute time per iteration for each operation
    norm_df = pd.DataFrame()
    norm_df['iterations'] = df['iterations']
    
    for group_name, operations in operation_groups.items():
        for op_code, op_name in operations.items():
            norm_df[op_code] = df[op_code] / df['iterations']
    
    # Create the bubble chart
    for g_idx, (group_name, operations) in enumerate(operation_groups.items()):
        group_color = COLORS[g_idx % len(COLORS)]
        
        for op_idx, (op_code, op_name) in enumerate(operations.items()):
            # Compute bubble sizes - inversely proportional to time per iteration
            # (faster operations get bigger bubbles)
            sizes = 1000 / (norm_df[op_code] * 1e9 + 1)  # Add 1 to avoid division by zero
            
            # Add slight offset to x position for better visibility
            x_pos = df['iterations'] * (1 + 0.05 * (op_idx - len(operations)/2))
            
            plt.scatter(x_pos, df[op_code], s=sizes, alpha=0.7, 
                       label=op_name, color=group_color, marker='o')
    
    plt.xscale('log')
    plt.yscale('log')
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.xlabel('Number of Iterations')
    plt.ylabel('Total Execution Time (seconds)')
    plt.title('Performance Comparison (Bubble Size = Efficiency)', fontweight='bold')
    
    # Format x-axis with K, M, B suffixes
    plt.gca().xaxis.set_major_formatter(FuncFormatter(format_large_number))
    
    # Place legend outside
    plt.legend(loc='center left', bbox_to_anchor=(1, 0.5))
    plt.tight_layout()
    
    bubble_file = os.path.join(output_dir, 'bubble_chart.png')
    plt.savefig(bubble_file, dpi=300, bbox_inches='tight')
    plt.close()
    print(f"📊 Bubble chart saved to {bubble_file}")
    
    # ---- 5. HEATMAP - TIME PER ITERATION ----
    # Normalized heatmap showing time per iteration for each operation
    
    plt.figure(figsize=(14, 10))
    
    # Prepare heatmap data - time per iteration (ns)
    heatmap_data = pd.DataFrame(index=norm_df['iterations'])
    for group_name, operations in operation_groups.items():
        for op_code, op_name in operations.items():
            # Convert to nanoseconds per iteration for better readability
            heatmap_data[op_name] = norm_df[op_code] * 1e9
    
    # Transpose so operations are rows and iterations are columns
    heatmap_data = heatmap_data.T
    
    # Plot heatmap
    im = plt.imshow(heatmap_data, cmap='viridis_r')  # viridis_r makes faster operations darker
    
    # Add colorbar
    cbar = plt.colorbar(im)
    cbar.set_label('Time per iteration (nanoseconds)', rotation=270, labelpad=20)
    
    # Configure axes
    plt.xlabel('Iterations')
    plt.ylabel('Operation')
    
    # Set x ticks to iteration values
    plt.xticks(np.arange(len(df['iterations'])), 
              [format_large_number(i, 0) for i in df['iterations']], 
              rotation=45)
    
    # Set y ticks to operation names
    plt.yticks(np.arange(len(heatmap_data.index)), heatmap_data.index)
    
    # Add text annotations in each cell with the time value
    for i in range(len(heatmap_data.index)):
        for j in range(len(heatmap_data.columns)):
            text = plt.text(j, i, f'{heatmap_data.iloc[i, j]:.2f}',
                          ha="center", va="center", color="w", fontsize=9)
    
    plt.title('Time per Iteration by Operation Type (nanoseconds)', fontweight='bold')
    plt.tight_layout()
    
    heatmap_file = os.path.join(output_dir, 'time_per_iteration_heatmap.png')
    plt.savefig(heatmap_file, dpi=300)
    plt.close()
    print(f"📊 Time-per-iteration heatmap saved to {heatmap_file}")
    
    # ---- 6. SCALING CHART ----
    # Shows how execution time scales with iteration count
    
    plt.figure(figsize=(14, 8))
    
    # Plot a line for each operation showing how it scales
    for g_idx, (group_name, operations) in enumerate(operation_groups.items()):
        plt.subplot(1, 3, g_idx+1)
        
        for op_idx, (op_code, op_name) in enumerate(operations.items()):
            # Calculate the scaling factor: time / iterations
            # Should be roughly constant if scaling is linear
            scaling = df[op_code] / df['iterations']
            
            # Normalize to the first value to show relative changes
            norm_scaling = scaling / scaling.iloc[0]
            
            plt.plot(df['iterations'], norm_scaling, marker='o', 
                   label=op_name, linewidth=2)
        
        plt.xscale('log')
        plt.grid(True, linestyle='--', alpha=0.7)
        plt.title(f'{group_name} Scaling', fontweight='bold')
        plt.xlabel('Number of Iterations')
        plt.ylabel('Relative Time per Iteration\n(normalized to smallest iteration)')
        
        # Format x-axis with K, M, B suffixes
        plt.gca().xaxis.set_major_formatter(FuncFormatter(format_large_number))
        
        plt.legend()
    
    plt.tight_layout()
    
    scaling_file = os.path.join(output_dir, 'scaling_chart.png')
    plt.savefig(scaling_file, dpi=300)
    plt.close()
    print(f"📊 Scaling chart saved to {scaling_file}")
    
    print(f"\n✅ All visualizations saved to directory: {output_dir}")
    
    return output_dir

def main():
    # Define iterations to test with a wider range from 10,000 to 10 billion
    iterations_list = [
        10_000,          # 10 thousand
        1_000_000,       # 1 million
        10_000_000,      # 10 million
        100_000_000,     # 100 million
        1_000_000_000,   # 1 billion
        10_000_000_000   # 10 billion
    ]
    
    print("🔢 Will test the following iteration counts:")
    for i, count in enumerate(iterations_list):
        print(f"  {i+1}. {count:,}")
    
    # Allow user to customize iteration counts
    customize = input("Would you like to customize these iteration counts? (y/n): ")
    if customize.lower() == 'y':
        print("Enter new iteration counts (comma separated, scientific notation allowed, e.g., 1e6,1e7):")
        try:
            user_input = input("> ")
            # Parse input allowing for scientific notation
            iterations_list = [int(float(x.strip())) for x in user_input.split(',') if x.strip()]
            print("Using these iteration counts:")
            for i, count in enumerate(iterations_list):
                print(f"  {i+1}. {count:,}")
        except ValueError:
            print("⚠️ Invalid input. Using default iterations.")
    
    # Run benchmarks
    results = run_benchmarks(iterations_list)
    
    if not results:
        print("❌ No benchmark results obtained.")
        return
    
    # Save results to CSV
    csv_file = save_to_csv(results)
    
    if csv_file:
        # Create visualizations
        viz_dir = create_visualizations(csv_file)
        print(f"\n🎉 Benchmark complete! Visualizations are in {viz_dir}")

if __name__ == "__main__":
    main()