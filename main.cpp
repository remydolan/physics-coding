#include <iostream>
#include <cmath>

using namespace std;

class Terrain{
private:
    float height;
    float width;
    float x_coord;
    float y_coord;
};

class Object{
private:
    float mass;
    float horizontal_velocity;
    float initial_horizontal_velocity;
    float initial_vertical_velocity;
    float vertical_velocity;
    //bearing is not relevant yet
    float bearing;
    float angle;
    float initial_velocity;
    float x_coord;
    float y_coord;
    float max_height;
    float vertical_height;
    float horizontal_distance;
    float current_velocity;
    float final_velocity;
    float acceleration;
    float time_step;
    float time_to_max_height;
    float total_time_of_flight;
    float initial_height;
    float final_horizontal_distance;
public:
    bool SetTimeStep(float t);
    float GetHorizontalVelocity();
    float GetCurrentVelocity();
    float GetXCoord();
    float HorizontalDistance(float t);
    float GetYCoord();
    bool SetTimeToMaxhHeight(float t);
    float CalculateHorizontalVelocity(float theta, float hypotenuse);
    float CalculateVerticalVelocity(float theta, float hypotenuse);
    Object(float mass, float initial_velocity, float x_coord, float y_coord, float acceleration, float theta);
    float VerticalVelocity(float t);
    float VerticalHeight(float t);
    bool CalculateMaxHeight(float t);
    bool SetTotalTimeOfFlight(float t);
    bool CalculateLaunchAngleFromBearing();
    bool CalculateFinalHorizontalDistance();
};

bool Object::CalculateFinalHorizontalDistance()
{
    final_horizontal_distance=total_time_of_flight*initial_horizontal_velocity;
    return true;
}

//need to find a way to make the object launchable from the right or the left, currently assuming from the left
bool Object::CalculateLaunchAngleFromBearing()
{
    if ((bearing<=90 && bearing>=0))
    {
        angle=90-bearing;
    }
    else if (bearing<=360 && bearing>=270)
    {
        angle=bearing-270;
    }
}

bool Object::CalculateMaxHeight(float t) {
    max_height=initial_height+(initial_vertical_velocity*t)+(acceleration*t*t/2);
    cout<<"the max height is "<<max_height<<endl;
}

float Object::GetHorizontalVelocity() {
    return horizontal_velocity;
}

float Object::VerticalHeight(float t) {
    y_coord=(initial_vertical_velocity*t)+(acceleration*t*t/2);
    return y_coord;
}

float Object::GetYCoord() {
    return y_coord;
}

bool Object::SetTimeToMaxhHeight(float t)
{
    time_to_max_height=t;
}

bool Object::SetTimeStep(float timestep) {
    time_step=timestep;
}

float Object::CalculateHorizontalVelocity(float theta, float hypotenuse)
{
    //might have to convert theta to radians
    return hypotenuse*cos(theta*M_PI/180);
}

float Object::CalculateVerticalVelocity(float theta, float hypotenuse)
{
    //might have to convert theta to radians
    return hypotenuse*sin(theta*M_PI/180);
}

Object::Object(float m, float v, float x, float y, float a, float theta)
{
    mass=m;
    initial_velocity=v;
    x_coord=x;
    y_coord=y;
    acceleration=a;
    angle=theta;
    horizontal_velocity=CalculateHorizontalVelocity(theta,v);
    vertical_velocity=CalculateVerticalVelocity(theta,v);
    initial_horizontal_velocity=CalculateHorizontalVelocity(theta,v);
    initial_vertical_velocity=CalculateVerticalVelocity(theta,v);
    initial_height=y;
    cout<<"the initial vertical velocity is "<<initial_vertical_velocity<<endl;
    cout<<"the initial and only horizontal velocity is "<<horizontal_velocity<<endl;
    cout<<"the initial height is "<<y_coord<<endl;
}
float Object::VerticalVelocity(float t) {
    vertical_velocity=initial_vertical_velocity+(acceleration*t);
    return vertical_velocity;
}


int main() {
    //program for doing projectile questions in Higher Physics
    float mass=1;
    float initial_velocity=10;
    float initial_y_coord=0;
    float initial_x_coord=0;
    float acceleration=-9.8;
    float launch_angle=30;
    Object ball(1,10,0,0,-9.8,30);
    bool finished=false;
    ball.SetTimeStep(0.001);
    float Time_Step=0.001;
    float time=0;
    float my_velcity;
    float my_height;
    //while loop for the first half of the trajectory
    while (finished==false)
    {
        time=time+Time_Step;
        cout<<"te value of time is "<<time<<endl;
        my_velcity=ball.VerticalVelocity(time);
        my_height=ball.VerticalHeight(time);
        cout<<"the vertical velocity is "<<my_velcity<<endl;
        cout<<"the vertical height is "<<my_height<<endl;
//        time=time+Time_Step;
        if (my_velcity<0)
        {
            finished=true;
            cout<<"the velocity is less than 0 at "<<time<<endl;
            ball.SetTimeToMaxhHeight(time);
            ball.CalculateMaxHeight(time);

        }
    }
    finished=false;
    //while loop for second half of the trajectory
    while (finished==false)
    {
        time=time+Time_Step;
        cout<<"te value of time is "<<time<<endl;
        my_velcity=ball.VerticalVelocity(time);
        my_height=ball.VerticalHeight(time);
        cout<<"the vertical velocity is "<<my_velcity<<endl;
        cout<<"the vertical height is "<<my_height<<endl;
//        time=time+Time_Step;
        if (ball.GetYCoord()<0)
        {
            finished=true;
            cout<<"the total time taken for trajectory is "<<time<<endl;
            cout<<"the horizontal distance covered is "<<ball.GetHorizontalVelocity()*time<<endl;

        }
    }
}
