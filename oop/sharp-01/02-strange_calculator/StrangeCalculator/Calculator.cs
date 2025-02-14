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
        double varX, varY, varZ, result;
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
            varX = varY = varZ = 0;
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
                case "y":
                    varY = val;
                    break;
                case "z":
                    varZ = val;
                    break;
                default:
                    string message = "Некорректное имя переменной " + var;
                    OnError?.Invoke(message);
                    throw new MissingMemberException(message);
            }
            Task.Run(() => Recalculate());
        }
        /// <summary>
        /// Функция, обновляющая result согласно актуальным значениям varX, varY и varZ
        /// </summary>
        public void Recalculate()
        {
            // левый множитель
            double mulLeft = Math.Pow(varX, 1d/3d);
            mulLeft += Math.Pow(varX, varY + 2);
            mulLeft *= 10;
            // правый множитель
            double mulRight = Math.Asin(varZ);
            mulRight *= mulRight;
            mulRight -= Math.Abs(varX - varY);

            result = mulLeft * mulRight;
            OnValueChanged?.Invoke(result);
        }
    }
}
