#ifndef COLOR_H
#define COLOR_H


class Color
{
    public:
        Color(){};
        Color(float r, float g, float b, float a);
        Color(const Color&);
        virtual ~Color();
        float getR() const { return _r; }
        void setR(float val) { _r = val; }
        float getG() const { return _g; }
        void setG(float val) { _g = val; }
        float getB() const { return _b; }
        void setB(float val) { _b = val; }
        float getA() const { return _a; }
        void setA(float val) { _a = val; }
    protected:
    private:
        float _r;
        float _g;
        float _b;
        float _a;
};

#endif // COLOR_H
