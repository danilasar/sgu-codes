using System;
// Посчитать сумму чётных элементов в столбцах и записать в новый массив
namespace ColumnSummator {
	class Program
	{
		static readonly long MaxN = (long)Math.Sqrt(long.MaxValue);
		static void Main(string[] args)
		{
			Console.Write("Размер массива: ");

			if (!long.TryParse(Console.ReadLine(), out long n) || n <= 0 || n >= MaxN) {
				Console.WriteLine("Ошибка: размер должен быть натуральным числом не больше {MaxN}");
				return;
			}

			long MaxNumber = long.MaxValue / (n * n);

			long[,] array = new long[n, n];
			long[] sums = new long[n];
			Console.WriteLine("Элементы массива построчно:");

			for (int i = 0; i < n; ++i) {
				Console.Write($"Строка {i + 1}: ");
				string[] input = Console.ReadLine().Split(' ');

				if (input.Length != n) {
					Console.WriteLine($"Ошибка: В строке должно быть {n} элементов.");
					--i;
					continue;
				}

				for (int j = 0; j < n; j++) {
					if (!long.TryParse(input[j], out array[i, j])) {
						Console.WriteLine($"Ошибка: '{input[j]}' - не число.");
						--i;
						break;
					}
					if(Math.Abs(array[i, j]) > MaxNumber) {
						Console.WriteLine($"Ошибка: '{input[j]}' не должно превышать по модулю {MaxNumber}.");
						--i;
						break;
					}
				}
			}

			for (int j = 0; j < n; ++j) {
				for (int i = 0; i < n; ++i) {
					if (array[i, j] % 2 == 0) {
						sums[j] += array[i, j];
					}
				}
			}

			Console.WriteLine("\nНовый массив:");
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					Console.Write(array[i, j] + "\t");
				}
				Console.Write("\r\n");
			}
		}
	}
}