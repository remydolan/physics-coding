#include <iostream>
#include <cmath>
#include <vector>

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
    //constant
    float mass;
    //constant
    float horizontal_velocity;
    //constant
    float initial_horizontal_velocity;
    //constant
    float initial_vertical_velocity;
    //array
    vector<float> vertical_velocity;
    int time_index=0;
    //bearing is not relevant yet
    float bearing;
    float angle;
    //constant
    float initial_velocity;
    //array
    vector<float> x_coord;
    //array
    vector<float> y_coord;
    //constant
    float max_height;
    //array
    //float vertical_height;
    //array
    //float horizontal_distance;
    //array
    vector<float> current_velocity;
    //constant
    float final_velocity;
    //constant
    float acceleration;
    //constant
    float time_step;
    //constant
    float time_to_max_height;
    //constant
    float total_time_of_flight;
    //constant
    float initial_height;
    //constant
    float final_horizontal_distance;
public:
    bool SetTimeStep(float t);
    float GetHorizontalVelocity();
    float GetVerticalVelocity(float t);
    float GetCurrentVelocity(float t);
    //float GetXCoord();
    float HorizontalDistance(float t);
    float GetYCoord(float t);
    //bool SetTimeToMaxhHeight(float t);
    float CalculateHorizontalVelocity(float theta, float hypotenuse);
    float CalculateVerticalVelocity(float theta, float hypotenuse);
    Object(float mass, float initial_velocity, float x_coord, float y_coord, float acceleration, float theta);
    ~Object();
    float VerticalVelocity(float t);
    float VerticalHeight(float t);
    //bool CalculateMaxHeight(float t);
    //bool SetTotalTimeOfFlight(float t);
    //bool CalculateLaunchAngleFromBearing();
    bool CalculateFinalHorizontalDistance();
    bool CalculateMaxHeightAndTimeToMaxHeight();
    bool CalculateFinalVelocity();
    bool CalculateTotalTimeOfFlight();
};


float Object::GetVerticalVelocity(float t) {
    int index=t/time_step;
    return vertical_velocity[index];
}
float Object::GetCurrentVelocity(float time)
{
    float vv=GetVerticalVelocity(time);
    float v=sqrt((GetHorizontalVelocity()*GetHorizontalVelocity())+vv*vv);
    current_velocity.push_back(v);
    return 1.0;
}

float Object::HorizontalDistance(float t)
{
    x_coord.push_back(t*initial_horizontal_velocity);
    return 1.0;
}

bool Object::CalculateTotalTimeOfFlight()
{
    total_time_of_flight=time_to_max_height+(final_velocity/acceleration);
}


bool Object::CalculateFinalHorizontalDistance()
{
    final_horizontal_distance=total_time_of_flight*initial_horizontal_velocity;
    return true;
}

bool Object::CalculateFinalVelocity() {
    final_velocity=-sqrt(2*-acceleration*max_height);
}

bool Object::CalculateMaxHeightAndTimeToMaxHeight() {
    //v=u+at
    time_to_max_height=-initial_vertical_velocity/acceleration;
    max_height=initial_height+(initial_vertical_velocity*time_to_max_height)+(acceleration*time_to_max_height*time_to_max_height/2);
}

//need to find a way to make the object launchable from the right or the left, currently assuming from the left
//bool Object::CalculateLaunchAngleFromBearing()
//{
//    if ((bearing<=90 && bearing>=0))
//    {
//        angle=90-bearing;
//    }
//    else if (bearing<=360 && bearing>=270)
//    {
//        angle=bearing-270;
//    }
//}

//bool Object::CalculateMaxHeight(float t) {
//    max_height=initial_height+(initial_vertical_velocity*t)+(acceleration*t*t/2);
//    cout<<"the max height is "<<max_height<<endl;
//}

float Object::GetHorizontalVelocity() {
    return horizontal_velocity;
}

float Object::VerticalHeight(float t) {
    y_coord.push_back((initial_vertical_velocity*t)+(acceleration*t*t/2));
    return 1.0;
}

float Object::GetYCoord(float t) {
    int index=t/time_step;
    return y_coord[index];
}

//bool Object::SetTimeToMaxhHeight(float t)
//{
//    time_to_max_height=t;
//}

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
    current_velocity.push_back(initial_velocity);
    x_coord.push_back(x);
    y_coord.push_back(y);
    acceleration=a;
    angle=theta;
    initial_horizontal_velocity=CalculateHorizontalVelocity(theta,v);
    horizontal_velocity=initial_horizontal_velocity;
    initial_vertical_velocity=CalculateVerticalVelocity(theta,v);
    initial_height=y;
    vertical_velocity.push_back(initial_vertical_velocity);
    CalculateMaxHeightAndTimeToMaxHeight();
    CalculateFinalVelocity();
    CalculateTotalTimeOfFlight();
    CalculateFinalHorizontalDistance();

}

Object::~Object() {
    cout << "the initial vertical velocity is " << initial_vertical_velocity << endl;
    cout << "the initial and only horizontal velocity is " << initial_horizontal_velocity << endl;
    //cout << "the initial height is " << y_coord << endl;
    //cout<<"the initial x coord is "<<x_coord<<endl;
    cout << "the max height is " << max_height << endl;
    cout << "the time to max height is " << time_to_max_height << endl;
    cout << "the final velocity is " << final_velocity << endl;
    cout << "the total time of flight is " << total_time_of_flight << endl;
    cout << "the final horizontal distance is " << final_horizontal_distance << endl;
    cout << "here is a vector full of vertical velocities: " << endl;
    int counter = 0;
//    for (int i = 0; i < vertical_velocity.size(); i++) {
//        //cout<<vertical_velocity[i]<<endl;
//        //cout<<"here is the value of i: "<<i<<endl;
//        if (vertical_velocity[i - 1] > 0 && vertical_velocity[i + 1] < 0) {
//            cout << "the time to max height is " << 0.0001 * (i) << endl;
//            cout << "the value of i is " << i << endl;
//            break;
//        }
//        if (i == vertical_velocity.size() - 1) {
//            counter = i;
//        }
//        }
//    cout << "here is a vector full of xcoords: " << endl;
//    for (int i = 0; i < x_coord.size(); i++) {
//        cout<<x_coord[i]<<endl;
//    }
//    cout << "here is a vector full of ycoords: " << endl;
//    for (int i = 0; i < y_coord.size(); i++) {
//        cout<<y_coord[i]<<endl;
//    }
//    cout << "here is a vector full of current veloc: " << endl;
//    for (int i = 0; i < current_velocity.size(); i++) {
//        cout<<current_velocity[i]<<endl;
//    }
        cout << "the value of counter is " << counter << endl;
    }
float Object::VerticalVelocity(float t) {
    vertical_velocity.push_back(initial_vertical_velocity+(acceleration*t));
    return 1.0;
}


int main() {
    //program for doing projectile questions in Higher Physics
    float mass=1;
    float initial_velocity=10;
    float initial_y_coord=0;
    float initial_x_coord=0;
    float acceleration=-9.8;
    float launch_angle=30;
    Object ball(mass,initial_velocity,initial_x_coord,initial_y_coord,acceleration,launch_angle);
    bool finished=false;
    float Time_Step=0.0001;
    ball.SetTimeStep(Time_Step);
    float time=0;
    float my_velcity;
    float my_height;
    float my_h_distance;
    while(finished==false)
    {
        time=time+Time_Step;
        my_velcity=ball.VerticalVelocity(time);
        my_height=ball.VerticalHeight(time);
        my_h_distance=ball.HorizontalDistance(time);
        ball.GetCurrentVelocity(time);
        cout<<"the vertical velocity is "<<my_velcity<<endl;
        cout<<"the vertical height is "<<my_height<<endl;
        cout<<"the y coord is "<<ball.GetYCoord(time)<<endl;
        if (ball.GetYCoord(time)<0)
        {
            finished=true;
        }
    }

//    bool finished=false;
//    ball.SetTimeStep(0.001);
//    float Time_Step=0.001;
//    float time=0;
//    float my_velcity;
//    float my_height;
//    //while loop for the first half of the trajectory
//    while (finished==false)
//    {
//        time=time+Time_Step;
//        cout<<"te value of time is "<<time<<endl;
//        my_velcity=ball.VerticalVelocity(time);
//        my_height=ball.VerticalHeight(time);
//        cout<<"the vertical velocity is "<<my_velcity<<endl;
//        cout<<"the vertical height is "<<my_height<<endl;
////        time=time+Time_Step;
//        if (my_velcity<0)
//        {
//            finished=true;
//            cout<<"the velocity is less than 0 at "<<time<<endl;
//            ball.SetTimeToMaxhHeight(time);
//            ball.CalculateMaxHeight(time);
//
//        }
//    }
//    finished=false;
//    //while loop for second half of the trajectory
//    while (finished==false)
//    {
//        time=time+Time_Step;
//        cout<<"te value of time is "<<time<<endl;
//        my_velcity=ball.VerticalVelocity(time);
//        my_height=ball.VerticalHeight(time);
//        cout<<"the vertical velocity is "<<my_velcity<<endl;
//        cout<<"the vertical height is "<<my_height<<endl;
////        time=time+Time_Step;
//        if (ball.GetYCoord()<0)
//        {
//            finished=true;
//            cout<<"the total time taken for trajectory is "<<time<<endl;
//            cout<<"the horizontal distance covered is "<<ball.GetHorizontalVelocity()*time<<endl;
//
//        }
//    }

}

