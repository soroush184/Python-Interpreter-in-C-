#include <bits/stdc++.h>
using namespace std;
int salam = 0;
bool flg = 0;
unordered_map<string, pair<string, string>> variables;
vector<string> yoMrWhite;
string rewrite(string s)
{
    for (auto &var : variables)
    {
        size_t start_pos = 0;
        while ((start_pos = s.find(var.first, start_pos)) != string::npos)
        {
            string val = var.second.second;
            if (var.second.first == "Int" || var.second.first == "Double")
            {
                if (val.find("\"") != string::npos)
                    val = val.substr(1, val.length() - 1);
                val = to_string(stod(val));
            }
            else if (var.second.first == "Str")
            {
                if (val.find("\"") == string::npos)
                    val = "\"" + val + "\"";
            }
            if ((s.substr(start_pos, 3) != "and") && (s.substr(start_pos, 2) != "or"))
            {
                s.replace(start_pos, var.first.length(), val);
                start_pos += val.length();
            }
            else if (var.second.first == "Str")
            {
                start_pos += var.first.length();
            }
            else
                start_pos += 2;
        }
    }
    return s;
}
bool isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}
bool isMath(string str)
{
    if ((str.find("+") != string::npos || str.find("-") != string::npos || str.find("*") != string::npos || str.find("/") != string::npos) && str.find("=") == string::npos)
        return 1;
    return 0;
}
bool isLogical(string str)
{
    if (str.find("==") != string::npos || str.find("<") != string::npos || str.find(">") != string::npos || str.find("!=") != string::npos || str.find(">=") != string::npos || str.find("<=") != string::npos || str.find(" and ") != string::npos || str.find(" or ") != string::npos)
        return 1;
    return 0;
}
int precedence(char c)
{
    if (c == '+' || c == '-')
        return 1;
    if (c == '*' || c == '/')
        return 2;
    return 0;
}

string postfix(string exp)
{
    stack<char> s;
    string postfixExp = "";
    int i = 0;
    while (i < exp.length())
    {
        if (isdigit(exp[i]) || exp[i] == '.')
        {
            while (isdigit(exp[i]) || exp[i] == '.')
            {
                postfixExp += exp[i];
                i++;
            }
            postfixExp += ' ';
        }
        else if (isOperator(exp[i]))
        {
            while (!s.empty() && precedence(s.top()) >= precedence(exp[i]))
            {
                postfixExp += s.top();
                postfixExp += ' ';
                s.pop();
            }
            s.push(exp[i]);
            i++;
        }
        else if (exp[i] == '(')
        {
            s.push(exp[i]);
            i++;
        }
        else if (exp[i] == ')')
        {
            while (!s.empty() && s.top() != '(')
            {
                postfixExp += s.top();
                postfixExp += ' ';
                s.pop();
            }
            if (!s.empty() && s.top() == '(')
                s.pop();
            i++;
        }
        else
        {
            i++;
        }
    }
    while (!s.empty())
    {
        postfixExp += s.top();
        postfixExp += ' ';
        s.pop();
    }
    return postfixExp;
}

double doMath(string exp)
{

    exp = postfix(exp);
    stack<double> nums;
    double result = 0;
    for (int i = 0; i < exp.length(); i++)
    {
        if (isdigit(exp[i]) || exp[i] == '.')
        {
            double operand = 0;
            while (isdigit(exp[i]) || exp[i] == '.')
            {
                if (exp[i] == '.')
                {
                    i++;
                    double fraction = 0.1;
                    while (isdigit(exp[i]))
                    {
                        operand += (exp[i] - '0') * fraction;
                        fraction *= 0.1;
                        i++;
                    }
                }
                else
                {
                    operand = operand * 10 + (exp[i] - '0');
                    i++;
                }
            }
            nums.push(operand);
        }
        else if (isOperator(exp[i]))
        {
            double b = nums.top();
            nums.pop();
            double a = nums.top();
            nums.pop();
            switch (exp[i])
            {
            case '+':
                nums.push(a + b);
                break;
            case '-':
                nums.push(a - b);
                break;
            case '*':
                nums.push(a * b);
                break;
            case '/':
                nums.push(a / b);
                break;
            }
        }
    }
    result = nums.top();
    return result;
}

bool isFloat(string s)
{
    if ((s.find(".")) != string::npos)
        return 1;
    return 0;
}
void save(string s)
{

    size_t pos = s.find('=');
    string var = s.substr(0, pos - 1);
    string val = s.substr(pos + 2);
    if (val.front() == '"' && val.back() == '"')
    {
        variables[var] = make_pair("Str", val);
    }
    else if (val.find("Int(input())") != string::npos)
    {
        salam++;
        variables[var] = make_pair("Int", yoMrWhite[salam]);
    }
    else if (val.find("Double(input())") != string::npos)
    {
        salam++;
        variables[var] = make_pair("Double", yoMrWhite[salam]);
    }
    else if (val.find("input()") != string::npos)
    {
        salam++;
        variables[var] = make_pair("Str", yoMrWhite[salam]);
    }
    else if (val.find("Int(") != string::npos)
    {
        size_t aa = val.find('(');
        size_t bb = val.find(')');
        string var2 = val.substr(aa + 1, val.length() - 5);
        int va = stoi(variables[var2].second);
        variables[var].second = to_string(va);
        variables[var].first = "Int";
    }
    else if (val.find("Double(") != string::npos)
    {

        size_t aa = val.find('(');
        size_t bb = val.find(')');
        string var2 = val.substr(aa + 1, val.length() - 8);
        variables[var].second = variables[var2].second;
        variables[var].first = "Double";
    }
    else
    {

        val = rewrite(val);
        int l = doMath(val);
        if (doMath(val) == l)
        {
            val = to_string(l);
            variables[var] = make_pair("Int", val);
        }
        else
        {
            double mmd = doMath(val);
            val = to_string(mmd);
            variables[var] = make_pair("Double", val);
        }
    }
}
string toInt(string var)
{
    if (variables[var].first == "Double" || variables[var].first == "Int")
    {
        int val = stoi(variables[var].second);

        return to_string(val);
    }
    else
    {
        int tmp = 0;
        for (char s : variables[var].second)
        {
            if (s == '.')
                break;
            tmp = tmp * 10 + (s - '0');
        }
        return to_string(tmp);
    }
}
string toDouble(string s)
{
    if (variables[s].first == "Double" || variables[s].first == "Int")
    {
        double out = stod(variables[s].second);
        stringstream stream;
        stream << fixed << setprecision(6) << to_string(out);
        stream.str();
    }
    else
    {
        double tmp = stod(variables[s].second);
        stringstream stream;
        stream << fixed << setprecision(6) << to_string(tmp);

        return stream.str();
        ;
    }
}
string getType(string var)
{
    return variables[var].first;
}
int getSize(string var)
{
    if (variables[var].first == "Str")
    {
        return variables[var].second.size();
    }
    else
    {
        return -1;
    }
}
double doOP(double a, double b, string op)
{
    if (op == "*")
        return a * b;
    else if (op == "/")
        return a / b;
    else if (op == "+")
        return a + b;
    else if (op == "-")
        return a - b;
    else if (op == "==")
        return a == b;
    else if (op == "!=")
        return a != b;
    else if (op == "<")
        return a < b;
    else if (op == "<=")
        return a <= b;
    else if (op == ">")
        return a > b;
    else if (op == ">=")
        return a >= b;
    else if (op == "and")
        return (bool)a && (bool)b;
    else if (op == "or")
        return (bool)a || (bool)b;
}

bool doOps(double a, double b, string op)
{
    if (op == "*")
        return a * b;
    else if (op == "/")
        return a / b;
    else if (op == "+")
        return a + b;
    else if (op == "-")
        return a - b;
    else if (op == "==")
        return a == b;
    else if (op == "!=")
        return a != b;
    else if (op == "<")
        return a < b;
    else if (op == "<=")
        return a <= b;
    else if (op == ">")
        return a > b;
    else if (op == ">=")
        return a >= b;
    else if (op == "and")
        return (bool)a && (bool)b;
    else if (op == "or")
        return (bool)a || (bool)b;
}
string postfixl(string salamDokhtari);
bool isstringval(string a, string b, string op)
{
    string tmp;
    for (int i = 0; i < a.length(); i++)
    {

        if (a[i] != ' ')
            tmp += a[i];
    }
    a = tmp;
    tmp = "";
    for (int i = 0; i < b.length(); i++)
    {

        if (b[i] != ' ')
            tmp += b[i];
    }
    b = tmp;
    tmp = "";
    for (int i = 0; i < op.length(); i++)
    {

        if (op[i] != ' ')
            tmp += op[i];
    }
    op = tmp;
    tmp = "";
    if (op == "==")
        return a == b;
    else if (op == "!=")
        return a != b;
}
int olaviat(char x, char y)
{
    if (x == '<' || x == '>' || x == '=' || x == '!' || x == '#' || (x == 'a' && y == 'n') || (x == 'o' && y == 'r'))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int isoperator(string x)
{
    if (x == ">=" || x == ">" || x == "==" || x == "<" || x == "<=" || x == "!=")
    {
        return 1;
    }
    else if (x == "and" || x == "or")
    {
        return 2;
    }
    else
    {
        return 0;
    }
}
bool solveLogic(string salamDokhtari)
{
    salamDokhtari = postfixl(salamDokhtari);
    stack<string> exps;
    string a = "";
    string b, c;
    double bb, cc;
    for (int i = 0; i < salamDokhtari.length(); i++)
    {
        do
        {
            while (salamDokhtari[i] == ' ')
            {
                i++;
            }
            a = "";
            while (salamDokhtari[i] != '#')
            {
                a += salamDokhtari[i];
                i++;
            }
            i++;
            if (!(isoperator(a)) && a != "")
            {
                exps.push(a);
            }
        } while (!(isoperator(a)) && i < salamDokhtari.length());
        b = exps.top();
        exps.pop();
        c = exps.top();
        exps.pop();
        if (b[0] == '"')
        {
            if (isstringval(c, b, a))
            {
                exps.push("1");
            }
            else
            {
                exps.push("0");
            }
        }
        else
        {
            bb = doMath(b);
            cc = doMath(c);
            if (doOps(cc, bb, a))
            {
                exps.push("1");
            }
            else
            {
                exps.push("0");
            }
        }
    }
    if (exps.top() != "0")
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

string postfixl(string salamDokhtari)
{
    int l = salamDokhtari.length();
    stack<string> s;
    string ans = "";
    string a = "";
    string x, k;
    for (int i = 0; i < l; i++)
    {
        while (salamDokhtari[i] == ' ')
        {
            i++;
        }
        while (!(olaviat(salamDokhtari[i], salamDokhtari[i + 1]) || salamDokhtari[i] == '(' || salamDokhtari[i] == ')' || i == l || (salamDokhtari[i] == 'a' && salamDokhtari[i + 1] == 'n' && salamDokhtari[i + 2] == 'd') || (salamDokhtari[i] == 'o' && salamDokhtari[i + 1] == 'r')))
        {
            ans += salamDokhtari[i];
            if (!(olaviat(salamDokhtari[i + 1], salamDokhtari[i + 2]) || salamDokhtari[i + 1] == '(' || salamDokhtari[i + 1] == ')' || i == l - 1 || (salamDokhtari[i + 1] == 'a' && salamDokhtari[i + 2] == 'n' && salamDokhtari[i + 3] == 'd') || (salamDokhtari[i + 1] == 'o' && salamDokhtari[i + 2] == 'r')))
            {
                i++;
            }
            else
            {
                ans += '#';
                break;
            }
        }
        if (salamDokhtari[i] == '(')
        {
            if (salamDokhtari[i + 6] == ')' && i == 0)
            {
                do
                {
                    if (salamDokhtari[i] == '<' || salamDokhtari[i] == '>' || salamDokhtari[i] == '!' || salamDokhtari[i] == '=' || salamDokhtari[i] == 'a' || salamDokhtari[i] == 'o')
                    {
                        s.push("(");
                        ans += '#';
                        break;
                    }
                    ans += salamDokhtari[i];
                    i++;
                } while (salamDokhtari[i] != ')');
            }
            else
            {
                s.push("(");
            }
        }
        else if (salamDokhtari[i] == ')')
        {
            do
            {
                x = s.top();
                s.pop();
                if (x != "(")
                {
                    ans += x;
                    ans += '#';
                }
            } while (!s.empty() && x != "(");
        }
        else if (olaviat(salamDokhtari[i], salamDokhtari[i + 1]))
        {
            while (salamDokhtari[i] != ' ')
            {
                a += salamDokhtari[i];
                i++;
            }
            if (isoperator(a))
            {
                if (s.empty())
                {
                    s.push(a);
                }
                else
                {
                    x = s.top();
                    if (x == "(")
                    {
                        s.push(a);
                    }
                    else
                    {
                        while (!s.empty() && !(x == "("))
                        {
                            k = x + '#';
                            ans += k;
                            s.pop();
                            if (!s.empty())
                            {
                                x = s.top();
                            }
                        }
                        s.push(a);
                    }
                }
                a = "";
            }
        }
        if (salamDokhtari[i] != '(')
        {
            ans += ' ';
        }
    }
    while (!s.empty())
    {
        x = s.top();
        k = x + '#';
        ans += k;
        s.pop();
    }
    return ans;
}

void solve(string s)
{
    if (s == "#")
        return;
    else if (s.find("Print(") != string::npos)
    {
        s = s.substr(6, s.length() - 7);
        string idk = rewrite(s);
        if (isLogical(s))
        {
            s = rewrite(s);
            cout << (solveLogic(s) ? "True" : "False") << endl;
        }
        else if (s.substr(0, 4) == "Size")
        {
            string tmp = s.substr(5, s.length() - 6);
            int size = getSize(tmp);
            if (size != -1)
                cout << size << endl;
        }
        else if (s.substr(0, 4) == "Type")
        {

            string tmp = s.substr(5, s.length() - 6);
            cout << getType(tmp) << endl;
        }
        else if (s.substr(0, 6) == "Double")
        {
            string tmp = s.substr(7, s.length() - 8);
            cout << toDouble(tmp);
        }

        else if (s.substr(0, 3) == "Int")
        {
            string tmp = s.substr(4, s.length() - 5);
            cout << toInt(tmp);
        }
        else if (s.find("[") != string::npos)
        {
            size_t pos = s.find('[');
            string var = s.substr(0, pos);
            string val = s.substr(pos);
            if (val.front() == '[' && val.back() == ']')
            {
                val = val.substr(1, val.size() - 2);
            }
            int ind = stod(val);
            string l = variables[var].second;
            if (ind < 0)
                cout << l[variables[var].second.length() + ind] << endl;
            else
                cout << l[ind] << endl;
        }
        else if (idk.find("\"") != string::npos && !isLogical(s))
        {
            cout << s.substr(1, s.length() - 2) << endl;
        }
        else
        {
            s = rewrite(s);
            int ss = doMath(s);
            if (ss == doMath(s))
                cout << ss << endl;
            else
            {
                cout << fixed << setprecision(6) << doMath(s) << endl
                     << fixed << setprecision(0);
            }
        }
    }
    else
        save(s);
}
string rewriteIf(string s)
{
    if (s.substr(0, 4) == "Size")
    {
        string tmp = s.substr(5, s.length() - 6);
        int size = getSize(tmp);
        tmp = to_string(size);
        return tmp;
    }
    else if (s.substr(0, 4) == "Type")
    {

        string tmp = s.substr(5, s.length() - 6);
        return getType(tmp);
    }
    else if (s.substr(0, 6) == "Double")
    {
        string tmp = s.substr(7, s.length() - 8);
        return toDouble(tmp);
    }

    else if (s.substr(0, 3) == "Int")
    {
        string tmp = s.substr(4, s.length() - 5);
        return toInt(tmp);
    }
    else if (s.find("[") != string::npos)
    {
        size_t pos = s.find('[');
        string var = s.substr(0, pos);
        string val = s.substr(pos);
        if (val.front() == '[' && val.back() == ']')
        {
            val = val.substr(1, val.size() - 2);
        }
        int ind = stod(val);
        string l = variables[var].second;
        if (ind < 0)
        {
            string m(1, l[variables[var].second.length() + ind]);
            return m;
        }
        else
        {
            string m(1, l[ind]);
            return m;
        }
    }
    else if (s.find("\"") != string::npos && !isLogical(s))
    {
        return s;
    }
    else if (isLogical(s))
    {
        s = rewrite(s);
        return to_string(solveLogic(s));
    }
    else
    {
        s = rewrite(s);
        return s;
    }
}
bool findIf(string s)
{
    s = s.substr(4, s.length() - 6);
    string dokhtari = "";
    string a = s;
    for (int i = 0; i < a.length(); i++)
    {
        size_t pos = s.find(' ');
        string var = s.substr(0, pos);
        s = s.substr(pos + 1);
        i += (var.length());
        if (isMath(var) || isLogical(var))
        {
            dokhtari += var;
        }
        else
        {
            dokhtari += rewriteIf(var);
        }
        dokhtari += ' ';
    }
    if (solveLogic(dokhtari))
        return 1;
    return 0;
}
bool isLoop(int num)
{
    for (int i = 0; i <= num; i++)
    {
        if (yoMrWhite[i].find("goto") != string::npos)
        {
            int n = stod(rewrite(yoMrWhite[i].substr(5)));
            if (n >= num && i != num)
                break;
            else if (i > n)
            {
                return 0;
            }
        }
    }
    return 1;
}

int tabs = 0;
int main()
{

    string s;
    int num = 0, check = 0;
    vector<string> gadid;
    while (getline(cin, s))
    {
        gadid.push_back(s);
        if (s == "#")
            break;
        num++;
    }
    /*if (!isLoop(num))
        cout << "Loop" << endl;
    else
    {*/

    int i = 0;
    while (true)
    {

        if (gadid[i] == "#")
        {
            yoMrWhite.push_back("#");
            break;
        }
        else if (gadid[i].find("while (") != string::npos)
        {
            int m = i;
            size_t pos = gadid[i].find('(');
            string ss = "if (";
            ss += gadid[i].substr(pos + 1);
            yoMrWhite.push_back(ss);
            i++;
            while (gadid[i][0] == '_')
            {
                yoMrWhite.push_back(gadid[i]);
                i++;
            }
            string l = "__goto ";
            l += to_string(m + 1);
            yoMrWhite.push_back(l);
            num++;
        }
        else
        {
            yoMrWhite.push_back(gadid[i]);
            i++;
        }
    }
    int k = 0;
    while (salam < num)
    {
        if (yoMrWhite[salam].find("goto") != string::npos)
        {
            int k = 0;
            string B = yoMrWhite[salam];
            while (B.substr(k)[0] == '_')
            {
                k++;
            }
            int n = stod(rewrite(B.substr(5 + k)));
            salam = --n;
            int bruh = 0;
            while (yoMrWhite[salam][bruh] == '_')
            {
                bruh += 2;
            }
            tabs = bruh;
        }
        if (yoMrWhite[salam].find("if (") != string::npos)
        {
            if (findIf(yoMrWhite[salam].substr(tabs)))
            {
                tabs += 2;
                salam++;
            }
            else
            {
                salam++;
                while (yoMrWhite[salam][tabs] == '_')
                {
                    salam++;
                }
                if (yoMrWhite[salam].find("else") != string::npos)
                {
                    salam++;
                    tabs += 2;
                }
            }
        }
        else
        {
            string A = yoMrWhite[salam];
            if (tabs == 0)
                check = 0;
            else
                check = tabs - 2;
            if (tabs == 0 || A[check] == '_')
            {
                while (A[0] == '_')
                    A = A.substr(2);
                if (A.find("else") != string::npos)
                {
                    salam++;
                    tabs += 2;
                    while (yoMrWhite[salam][tabs] == '_')
                    {
                        salam++;
                        if (salam == num)
                        {
                            break;
                        }
                    }
                }
                else
                {
                    solve(A);
                    salam++;
                }
            }
            else
            {
                while (tabs > 0)
                {
                    tabs -= 2;
                    if (yoMrWhite[salam][tabs] == '_')
                    {
                        break;
                    }
                }
            }
        }
    }
    //}
    return 0;
}