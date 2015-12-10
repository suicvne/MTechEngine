#ifndef MATHSSTUFF_H
#define MATHSSTUFF_H

class MathsStuff
{
    public:
        static int math_clamp(int compare, int _min, int _max)
        {
            return ((compare > _max) ? _max : (compare < _min) ? _min : ((compare < _max && compare > _min) ? compare : compare));

        //    This is equivalent code. I was just showing off to my friends that I can one line it

        //    if(compare > _max)
        //        return _max;
        //    if(compare < _min)
        //        return _min;
        //    if(compare < _max && compare > _min)
        //    {
        //        return compare;
        //    }
        };
    private:
        MathsStuff();
};

#endif // MATHSSTUFF_H
