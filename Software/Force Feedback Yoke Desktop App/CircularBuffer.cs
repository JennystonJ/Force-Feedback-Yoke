using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Force_Feedback_Yoke_Desktop_App
{
    internal class CircularBuffer<T>
    {
        private T[] items;
        private int headIndex = 0;
        private int tailIndex = 0;
        
        public int Count { get; set; } = 0;

        public CircularBuffer(int size)
        {
            items = new T[size];
        }

        public T[] ToArray()
        {
            if(Count == 0)
            {
                return Array.Empty<T>();
            }

            T[] array = new T[Count];
            for (int i = 0; i < Count; i++)
            {
                array[i] = Get(i);
            }

            return array;
        }

        public T Get(int index)
        {
            return items[(headIndex + index) % items.Length];
        }

        public void Add(T item)
        {
            tailIndex++;
            // Check for overflow
            if(tailIndex == items.Length)
            {
                tailIndex = 0;
            }

            // Add item to buffer
            items[tailIndex] = item;

            // Check if max count has not been reached then increment count
            if (Count != items.Length)
            {
                Count++;
            }
            // Max count has been reached
            else
            {
                // Move head index forward since current index has been overwritten
                headIndex++;
            }
        }
    }
}
