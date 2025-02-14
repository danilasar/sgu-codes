using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace StrangeCalculator
{
    /// <summary>
    /// Переменная из математической формулы из задания позволяет отслеживать события ввода в реальном времени
    /// </summary>
    class VariableState<T>
    {
        /// <summary>
        /// Последнее корректное значение переменной
        /// </summary>
        public T Value;
        /// <summary>
        /// Является ли последнее введённое значение корректным?
        /// </summary>
        public bool IsGood;
        /// <summary>
        /// Соответствует ли последнее введённое значение тому, с которым работает сумматор?
        /// </summary>
        public bool IsChanged;
        public VariableState(T value = default(T))
        {
            Value = value;
            IsChanged = IsGood = false;
        }
    }
}
