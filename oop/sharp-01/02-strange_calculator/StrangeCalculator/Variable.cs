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
    class Variable
    {
        /// <summary>
        /// Последнее корректное значение переменной
        /// </summary>
        public double Value;
        /// <summary>
        /// Является ли последнее введённое значение корректным?
        /// </summary>
        public bool IsGood;
        /// <summary>
        /// Соответствует ли последнее введённое значение тому, с которым работает сумматор?
        /// </summary>
        public bool IsChanged;
        public Variable(double value)
        {
            Value = value;
            IsChanged = IsGood = false;
        }
        /// <summary>
        /// Создаёт состояние переменной с начальным значением 0
        /// </summary>
        public Variable() : this(0) { }
    }
}
