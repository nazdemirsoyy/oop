#ifndef WEATHER_H
#define WEATHER_H

class Plain;
class Grassland;
class Lake;

class Weather
{
    public:
        virtual void change(Plain *p) = 0;
        virtual void change(Grassland *p) = 0;
        virtual void change(Lake *p) = 0;
        virtual ~Weather() {}
        static int humidity;
};

class Sunny : public Weather
{
    public:
        static Sunny* instance();
        void change(Plain *p);
        void change(Grassland *p);
        void change(Lake *p);
        static void destroy();
    protected:
        Sunny(){}
    private:
        static Sunny* _instance;
};

class Cloudy : public Weather
{
    public:
        static Cloudy* instance();
        void change(Plain *p);
        void change(Grassland *p);
        void change(Lake *p);
        static void destroy();
    protected:
        Cloudy(){}
    private:
        static Cloudy* _instance;
};

class Rainy : public Weather
{
    public:
        static Rainy* instance();
        void change(Plain *p);
        void change(Grassland *p);
        void change(Lake *p);
        static void destroy();
    protected:
        Rainy(){}
    private:
        static Rainy* _instance;
};

#endif // WEATHER_H
