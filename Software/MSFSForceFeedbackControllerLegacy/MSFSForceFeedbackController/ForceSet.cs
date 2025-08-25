using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Reflection.Metadata;
using System.Text;
using System.Threading.Tasks;

namespace MSFSForceFeedbackController
{
    public class ForceSet
    {
        public double Constant { get; set; }
        public double Spring {  get; set; }
        public double Damper { get; set; }
        public ForceSet() 
        {
            Constant = 0.0f;
            Spring = 0.0f;
            Damper = 0.0f;
        }
        public ForceSet(double constant, double spring, double damper)
        {
            Constant = constant;
            Spring = spring;
            Damper = damper;
        }

        public static ForceSet operator +(ForceSet lhs, ForceSet rhs)
        {
            return new ForceSet
            {
                Constant = lhs.Constant + rhs.Constant,
                Spring = lhs.Spring + rhs.Spring,
                Damper = lhs.Damper + rhs.Damper
            };
        }

        public static ForceSet operator *(ForceSet lhs, double rhs)
        {
            return new ForceSet
            {
                Constant = lhs.Constant * rhs,
                Spring = lhs.Spring * rhs,
                Damper = lhs.Damper * rhs
            };
        }

        public static ForceSet operator *(ForceSet lhs, ForceSet rhs)
        {
            return new ForceSet
            {
                Constant = lhs.Constant * rhs.Constant,
                Spring = lhs.Spring * rhs.Spring,
                Damper = lhs.Damper * rhs.Damper
            };
        }

        public void Add(ForceSet other)
        {
            Constant += other.Constant;
            Spring += other.Spring;
            Damper += other.Damper;
        }

    }
}
