using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StrangeCalculator.Calculator
{

    /// <summary>
    /// Индексатор математических переменных. Нужен для хранения значений переменных математической функции, работает как словарь с enum-ключом.
    /// </summary>
    public class VariablesIndexer<T> : IDictionary<Variable, T>, IEnumerable<KeyValuePair<Variable, T>>
    {
        T defaultValue;
        /// <summary>
        /// Словарь для хранения связей между переменными и их значениями
        /// </summary>
        Dictionary<Variable, T> args;


        /// <summary>
        /// Делегат функции обработчика изменившегося значения переменной
        /// </summary>
        /// <param name="variable">Переменная</param>
        /// <param name="newValue">Значение</param>
        public delegate void ValueHandler(Variable variable, T newValue);

        /// <summary>
        /// Событие изменившегося значения переменной
        /// </summary>
        public ValueHandler OnVariableChanged;

        
        /// <summary>
        /// По умолчанию всем переменным присваивается нулевое значение, но оно может быть изменено. В таком случае бросится событие OnVariableChanged
        /// </summary>
        /// <param name="index">Переменная</param>
        /// <returns>Значение переменной</returns>
        public T this[Variable index]
        {
            get {
                if (!args.ContainsKey(index)) {
                    args.Add(index, defaultValue);
                }
                return args[index];
            }
            set {
                if (!args.ContainsKey(index)) {
                    args.Add(index, defaultValue);
                }
                args[index] = value;
                OnVariableChanged?.Invoke(index, value);
            }
        }

        public ICollection<Variable> Keys => ((IDictionary<Variable, T>)args).Keys;

        public ICollection<T> Values => ((IDictionary<Variable, T>)args).Values;

        public int Count => ((ICollection<KeyValuePair<Variable, T>>)args).Count;

        public bool IsReadOnly => ((ICollection<KeyValuePair<Variable, T>>)args).IsReadOnly;
        /// <summary>
        /// Создаёт экземпляр индексатора переменных
        /// </summary>
        /// <param name="defaultValue">Значение переменных по умолчанию</param>

        public VariablesIndexer(T defaultValue = default(T)) {
            this.defaultValue = defaultValue;
            args = new Dictionary<Variable, T>();
        }

        public IEnumerator<KeyValuePair<Variable, T>> GetEnumerator()
        {
            return args.GetEnumerator();
            //return ((IEnumerable<KeyValuePair<Variable, T>>)args).GetEnumerator();
        }

        public bool ContainsKey(Variable key)
        {
            return ((IDictionary<Variable, T>)args).ContainsKey(key);
        }

        public void Add(Variable key, T value)
        {
            ((IDictionary<Variable, T>)args).Add(key, value);
        }

        public bool Remove(Variable key)
        {
            return ((IDictionary<Variable, T>)args).Remove(key);
        }

        public bool TryGetValue(Variable key, out T value)
        {
            return ((IDictionary<Variable, T>)args).TryGetValue(key, out value);
        }

        public void Add(KeyValuePair<Variable, T> item)
        {
            ((ICollection<KeyValuePair<Variable, T>>)args).Add(item);
        }

        public void Clear()
        {
            ((ICollection<KeyValuePair<Variable, T>>)args).Clear();
        }

        public bool Contains(KeyValuePair<Variable, T> item)
        {
            return ((ICollection<KeyValuePair<Variable, T>>)args).Contains(item);
        }

        public void CopyTo(KeyValuePair<Variable, T>[] array, int arrayIndex)
        {
            ((ICollection<KeyValuePair<Variable, T>>)args).CopyTo(array, arrayIndex);
        }

        public bool Remove(KeyValuePair<Variable, T> item)
        {
            return ((ICollection<KeyValuePair<Variable, T>>)args).Remove(item);
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return ((IEnumerable)args).GetEnumerator();
        }
    }
}
