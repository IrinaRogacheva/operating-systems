#include "recursive_descent.h"

bool E(std::string& str)
{
    if (T(str))
    {
        return M(str);
    }
    else
    {
        return false;
    }
}

bool F(std::string& str)
{
    if (str[0] == '-')
    {
        str.erase(0, 1);
        F(str);
    }
    else if (str[0] == '(')
    {
        str.erase(0, 1);
        if (str[str.size() - 1] == ')')
        {
            str.erase(str.size() - 1, 1);
            return E(str);
        }
        else
        {
            return false;
        }
    }
    else if (str[0] == '7')
    {
        str.erase(0, 1);
        return true;
    }
    else if (str[0] == 'a')
    {
        str.erase(0, 1);
        return true;
    }
    else
    {
        return false;
    }
}

bool N(std::string& str)
{
    if ((str[0] == '*'))
    {
        str.erase(0, 1);
        if (F(str))
        {
            if (!N(str))
            {
                return false;
            }
        }
        else
        {
            return false;
        }
        return true;
    }
    else if (str == "")
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool T(std::string& str)
{
    if (F(str))
    {
        if (!N(str))
        {
            return false;
        }
        return true;
    }
    return false;
}

bool M(std::string& str)
{
    if ((str[0] == '+'))
    {
        str.erase(0, 1);
        if (T(str))
        {
            if (!M(str))
            {
                return false;
            }
        }
        else
        {
            return false;
        }
        return true;
    }
    else if (str == "")
    {
        return true;
    }
    else
    {
        return false;
    }
}

void CheckExpression(std::istream& is, std::ostream& os)
{
    std::string str;
    getline(is, str);

    if (F(str))
    {
        os << "Ok\n";
    }
    else
    {
        os << "Error\n";
    }
}