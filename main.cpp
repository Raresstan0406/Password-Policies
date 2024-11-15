#include <bits/stdc++.h>

using namespace std;

class Policy
{
protected:
    bool isChecked;
public:
    virtual void check(const string &parola)=0;
    bool getCheck()const
    {
        return isChecked;
    }
};


class LengthPolicy : public Policy
{
private:
    uint16_t minLength;
    uint16_t maxLength;
public:
    LengthPolicy(uint16_t min)
    {
        minLength=min;
        maxLength=255;
    }
    LengthPolicy(uint16_t min, uint16_t max)
    {
        minLength=min;
        maxLength=max;
    }

    void check(const string &parola)
    {
        if((parola.size()>=minLength && parola.size()<=maxLength))
            isChecked=true;
        else
            isChecked=false;
    }
};


class ClassPolicy : public Policy
{
private:
    uint16_t minClassCount;
public:
    ClassPolicy(uint16_t min)
    {
        minClassCount=min;
    }
    void check(const string &parola)
    {
        int c1=0,c2=0,c3=0,c4=0;
        for(int i=0;i<parola.size();i++)
        {
            if(islower(parola[i]))
                c1=1;
            else
            if(isupper(parola[i]))
                c2=1;
            else
            if(isdigit(parola[i]))
                c3=1;
            else
                c4=1;
        }
        int c= c1+c2+c3+c4;
        if(c>=minClassCount)
            isChecked=true;
        else
            isChecked=false;

    }
};

class IncludePolicy : public Policy
{
private:
    char characterType;
public:
    IncludePolicy(char a)
    {
        characterType=a;
    }
    void check(const string &parola)
    {
        int ct=0;
        isChecked=false;
        if(isupper(characterType))
        {
            for(int i=0;i<parola.size();i++)
                if(isupper(parola[i]))
                {
                    isChecked=true;
                }
        }
        else
        if(islower(characterType))
        {
            for(int i=0;i<parola.size();i++)
                if(islower(parola[i]))
                {
                    isChecked=true;
                }
        }
        else
        if(isdigit(characterType))
        {
            for(int i=0;i<parola.size();i++)
                if(isdigit(parola[i]))
                {
                    isChecked=true;
                }
        }
        else
        if(!isupper(characterType) && !islower(characterType) && !isdigit(characterType))
        {
            for(int i=0;i<parola.size();i++)
                if(!isupper(parola[i]) && !islower(parola[i]) && !isdigit(parola[i]))
                {
                    isChecked=true;
                }
        }

    }
};


class NotIncludePolicy : public Policy
{
private:
    char characterType;
public:
    NotIncludePolicy(char a)
    {
        characterType=a;
    }
    void check(const string &parola)
    {
        isChecked=true;
        if(isupper(characterType))
        {
            for(int i=0;i<parola.size();i++)
                if(isupper(parola[i]))
                {
                    isChecked=false;
                }
        }
        else
        if(islower(characterType))
        {
            for(int i=0;i<parola.size();i++)
                if(islower(parola[i]))
                {
                    isChecked=false;
                }
        }
        else
        if(isdigit(characterType))
        {
            for(int i=0;i<parola.size();i++)
                if(isdigit(parola[i]))
                {
                    isChecked=false;
                }
        }
        else
        if(!isupper(characterType) && !islower(characterType) && !isdigit(characterType))
        {
            for(int i=0;i<parola.size();i++)
                if(!isupper(parola[i]) && !islower(parola[i]) && !isdigit(parola[i]))
                {
                    isChecked=false;
                }
        }


    }
};


class RepetitionPolicy : public Policy
{
private:
    uint16_t maxCount;
public:
    RepetitionPolicy(uint16_t max)
    {
        maxCount=max;
    }
    void check(const string &parola)
    {
        int ct=1;
        isChecked=true;
        for(int i=1;i<parola.size();i++)
        {
            if(parola[i-1]==parola[i])
            {
                ct++;
            }
            else
                ct=1;
            if(ct>maxCount)
                isChecked=false;
        }

    }
};


class ConsecutivePolicy : public Policy
{
private:
    uint16_t maxCount;
public:
    ConsecutivePolicy(uint16_t max)
    {
        maxCount=max;
    }
    void check(const string &parola)
    {
        int ct=1;
        isChecked=true;
        for(int i=1;i<parola.size();i++)
        {
            if(parola[i-1]+1==parola[i])
            {
                ct++;
            }
            else
                ct=1;
            if(ct>maxCount)
                isChecked=false;
        }
    }
};


string checkPassword(string x, vector <Policy *> y)
{
    for(int i=0;i<y.size();i++)
    {
        y[i]->check(x);
        if(y[i]->getCheck()==false)
        {
            return "NOK";
        }
    }
    return "OK";
}

int main()
{
    vector <Policy *> politici;
    string v[100];
    int k=0;
    uint16_t n, min, max=255;
    string cerinta, parola;
    char inc;
    uint16_t cons, rep, nr;
    cin >> n;
    for(int i=0; i<n;i++)
    {
        cin >> cerinta;
        if(cerinta =="length")
        {
            cin >> min;
            if (min<6)
                cin >> max;
            politici.push_back(new LengthPolicy(min,max));
        }
        if(cerinta =="include")
        {
            cin >> inc;
            politici.push_back(new IncludePolicy(inc));
        }
        if(cerinta =="ninclude")
        {
            cin >> inc;
            politici.push_back(new  NotIncludePolicy(inc));
        }
        if(cerinta =="repetition")
        {
            cin >> rep;
            politici.push_back(new RepetitionPolicy(rep));
        }
        if(cerinta =="consecutive")
        {
            cin >> cons;
            politici.push_back(new ConsecutivePolicy(cons));
        }
        if(cerinta =="class")
        {
            cin >> nr;
            politici.push_back(new ClassPolicy(nr));
        }
    }
    while( cin >> parola)
    {
        cout << checkPassword(parola,politici) << '\n';
    }
    return 0;
}