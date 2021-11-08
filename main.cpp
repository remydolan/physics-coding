#include <iostream>
#include <cmath>

using namespace std;

const bool SolveQuadratic(float& a, float& b, float& c)
{
    float discriminant=abs(b*b)-(4*a*c);
    if (discriminant<0)
    {
        discriminant=abs(discriminant);
        float real=(-b)/(2*a);
        float complex1=sqrt(discriminant)/(2*a);
        float complex2=-sqrt(discriminant)/(2*a);
        cout<<"the solution is "<<real<<"+"<<complex1<<"i"<<" and "<<real<<complex2<<"i"<<endl;
    }
    else
    {
        float positive_x=(-b+sqrt(discriminant))/(2*a);
        float negative_x=(-b-sqrt(discriminant))/(2*a);
        cout<<"the solution is "<<positive_x<<" and "<<negative_x<<endl;
    }
}

int main()
{
float a=1;
float b=-6;
float c=9;
SolveQuadratic(a,b,c);
}
