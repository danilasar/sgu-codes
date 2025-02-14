using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StrangeCalculator
{
    /// <summary>
    /// Вычислитель, отвечающий за поиск значения функции при заданных x, y, z
    /// </summary>
    class Calculator
    {
        double varX, varB, result;
        public delegate double Function(double x);
        public Function funcF;
        /// <summary>
        /// Обработчик событий ошибки
        /// </summary>
        /// <param name="s">Описание ошибки</param>
        public delegate void ErrorHandler(string s);
        /// <summary>
        /// Обработчик событий изменившегося значения
        /// </summary>
        /// <param name="result">Новое значение функции</param>
        public delegate void ValueHandler(double result);
        /// <summary>
        /// Событие, связанное с ошибкой обновления переменных или перевычисления
        /// </summary>
        public ErrorHandler OnError;
        /// <summary>
        /// Событие, которое происходит при перевычислении значения функции
        /// </summary>
        public ValueHandler OnValueChanged;
        /// <summary>
        /// Создаёт объект вычислителя и тут же определяет result для x, y и z
        /// </summary>
        public Calculator()
        {
            varX = varB = 0;
            funcF = (x) => x;
            Task.Run(() => Recalculate());
        }
        /// <summary>
        /// Функция, обновляющая актуальное значение переменной
        /// </summary>
        /// <param name="var">Имя переменной из формулы в нижнем регистре</param>
        /// <param name="val">Новое значение переменной</param>
        /// <exception cref="MissingMemberException">Заданной переменной не существует</exception>
        public void ChangeVariable(string var, double val)
        {
            switch(var)
            {
                case "x":
                    varX = val;
                    break;
                case "b":
                    varB = val;
                    break;
                default:
                    string message = "Некорректное имя переменной " + var;
                    OnError?.Invoke(message);
                    throw new MissingMemberException(message);
            }
            Task.Run(() => Recalculate());
        }

        /// <summary>
        /// Изменяет функцию
        /// </summary>
        /// <param name="func">Имя функции</param>
        /// <param name="val">Функция</param>
        public void ChangeFunction(string func, Function val) {
            switch(func) {
                case "f":
                    funcF = val;
                    break;
                default:
                    string message = "Некорректное имя функции " + func;
                    OnError?.Invoke(message);
                    throw new MissingMemberException(message);
            }
        }
        /// <summary>
        /// Функция, обновляющая result согласно актуальным значениям varX, varY и varZ
        /// </summary>
        public void Recalculate()
        {
            double xb = varX * varB;
            double funcResult = funcF(varX);
            if(0.5 < xb && xb < 10) {
                result = Math.Exp(funcResult - Math.Abs(varB));
            } else if(0.1 < xb && xb < 0.5) {
                result = Math.Sqrt(Math.Abs(funcResult + varB));
            } else {
                result = 2 * funcResult * funcResult;
            }
            OnValueChanged?.Invoke(result);
        }
    }
}
