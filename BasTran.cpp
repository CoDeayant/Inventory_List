
#include <iostream>
#include <fstream>

using namespace std;
const short max_len = 256;

bool isdigit(char c)
{
    return (c >= '0' && c <= '9');
}

bool isspace(char c)
{
    return (c == ' ');
}

bool issign(char c)
{
    return (c == '-' || c == '+');
}

bool isdot(char c)
{
    return (c == '.' || c == ',');
}

bool parse_number(char * t) {
    
    bool digit = (*t != 0); // !!*t
                            // символ '\0' имеет код = 0 (If symbol '\0' == 0)
    bool dot = false;

    while (digit && isspace(*t)) ++t; // пропустить пробелы (Skip the space symbol)


    if (digit && issign(*t) )    // текущий символ - знак (is that symbol is sign)

        digit = isdigit(* ++t); // проверить есть ли после знака цифра (if after symbol we have a number)

    while ( digit && *t ) {
       
        if (isdot(*t))
        {
            if (!dot) {
                dot = true;

                digit = isdigit(*++t);
            }
            else {
                digit = false;
            };
        }
         if (digit)
            digit = isdigit(*t++); // проверяем текущий символ - цифра (if next symbol is digit)
                               // переходим к следующему символу (Going for next symbol)


    }
    
    return (digit); // результат (result)

    // return false - НИКОГДА ТАК НЕ ДЕЛАТЬ! (NEVER DO THIS)
}

int char_to_num(char c) {
    return (c - '0'); // преобразуем цифру в число (transform int into number)
}

double string_to_double(char* t) {

    bool minus = false;

    double res = 0;

    double sub = 0.1;

    bool dot = false;

    while (isspace(*t)) ++t; // пропустить пробелы (Skip the space sign)
    
    if (issign(*t)) minus = (*t++ == '-'); // символ - минус (if we find - symbol , for negative numbers)

    while (*t && !isdot(*t)) {  // проходим по целой части (going through the whole part)
        res = res * 10 + char_to_num(*t++);
    }

    while ( *t ) {  // проходим по дробной части //(going through fractional part)
        res += sub * char_to_num(*t);
        sub /= 10;
    }

    return ( minus ? -(res) : res);

}


void compile(ifstream& file_in, ofstream& file_out ) {

    char text_in[max_len] = "\0";
    char text_out[max_len] = "\0";

    int line = 0;

    while (!file_in.eof()) {
        file_in.getline(text_in, max_len, '\n'); // считываем строку до переноса строки (Reading line till the '\n' sign)
        file_out << "Line " << ++line << ": " << endl << text_in << endl; // записываем в выходной файл (Writing in output file)
                                                                         // увеличиваем счетчик строк line++ (Increasing line count)
        if (parse_number(text_in))
        {
            file_out << "Number " << endl;
            file_out << "Value = " << string_to_double (text_in) << endl;

        }
        else {
            file_out << "Not a Number " << endl;
        }

    }


}


int main()
{
    ifstream file_in;
    file_in.open("input.txt");

    ofstream file_out;
    file_out.open("output.txt");

    compile(file_in, file_out);

    file_in.close();
    file_out.close();


}


/**/
// //Это я кодил для 1.2 таска 
// #include <iostream>

// using namespace std;

// void get_value(int &change_value)
// {
//     std::cout << "Enter new value: ";
//     std::cin >> change_value;
// }
// std::string hex_convert(int num)
// {
//     std::string hex_num = "";
//     int remain;
//     char strremain = ' ';
//     do
//     {
//         remain = num%16;
//         if (remain < 10)
//         {
//             strremain = '0' + remain;
//         }
//         else
//         {
//             strremain = 'A' + (remain - 10);
//         }
//         hex_num.insert(0,1,strremain);
//         num = num/16;   
//     }
//     while(num != 0);
//     return hex_num;
// }
// int main()
// {
//     int ival, ival1, ival2;

//     // get_value(ival);
//     // get_value(ival1);
//     // get_value(ival2);
    
//     /*Task 1 - A Mistake is that else is written within if, and not separated by curved brackets
//     if (ival1 != ival2)
//     {
//         ival1 = ival2;
//     }
//     else
//     {
//         ival1 = ival2 = 0;
//     }*/

//     /*Task 2 - A Mistake was ,that we tried to initialize val in if statement, and not outside
//     int val;
//     get_value(val);
//     if (val)
//     {
//         std::cout << "val = " << val << "\n"; // Enters val value
//     }
//     if (!val)
//     {
//         std::cout << "val = \n"; //Enters val empty, and skips to next line
//     }*/
    
//     /*Task 3 - A mistake is misusing = and == operators
//     if (ival == 0)
//     {
//         std::cout << "Are you sure you want ival to be equal to 0?: ";
//         get_value(ival);
//     }
//     */
    
//     /*Task 4 - A mistake is that if statement didn't do anything, and was is a way of else statement
//     if ( ival == 0 )
//     {
//         std::cout << "Ival is equal to zero: " << "\n";
//     } 
//     else 
//     {
//         std::cout << "Ival was already equal to zero: " << "\n";
//         ival = 0;
//     }*/

//     /*Task 5- Mistake is that switch case y itself won't count all the numbers, so we can't count more than 1 number here and no breaks in case 
//     int aCnt = 0 ; int eCnt = 0; int iouCnt = 0;
//     std::string hex;
    
//     hex = hex_convert(10346);

//     cout << hex << '\n';

//     int hex_len = hex.length();
//     for(int i = 0; i < hex_len;i++)
//     {
//         if (hex[i] == 'A')
//         {
//             aCnt += 1;
//         }
//         else if (hex[i] == 'E')
//         {
//             eCnt += 1;
//         }
//         else
//         {
//             iouCnt += 1;
//         }
//     }
//     cout << aCnt << " " << eCnt << " " << iouCnt << "\n";
//     */
    
//     /*Task 6 -Mistake is that we cannot check more than one condition in one case, they should be separated, + we again don't count anything, we check only one number 
//     int oddcnt = 0, evencnt = 0;

//     int trycnt = 0;
//     cout << "How many numbers would you like to check?: ";
//     cin >> trycnt;

//     int check_num;
//     for (int i = 0; i <trycnt;i++)
//     {
//         cout << "Enter the number you would like to check: ";
//         cin >> check_num;

//         if (check_num%2 == 0)
//         {
//             evencnt += 1;
//         }
//         else
//         {
//             oddcnt += 1;
//         }
//     }
//     cout << "Odd number amount: " << oddcnt << " " << "Even number ammount: " << evencnt << "\n";

//     */
//     return 0;
// }



/*
//Это тесты для 2-мерных массивов:
#include <iostream>

using namespace std;

void Reverse(int *arr[], int rows, int cols)
{
    for (int i = 0; i < rows;i++){
        for (int j = 0 ; j < cols;j++){
            arr[i][j] = arr[rows-i-1][cols-j-1]; 
        }
        cout << "\n";
    }
}
int main(){
    int rows, cols;

    cout << "Choose a row size for your array: ";
    cin >> rows;

    cout << "Choose a cols size for your array: ";
    cin >> cols;

    int **double_arr = new int*[rows];
    for (int i =0; i < rows;i++){
        double_arr[i] = new int[cols];
        int fill_num;
        for (int j = 0 ; j < cols;j++){
            cout << "Enter a number for a " << i << ";" << j << " place: ";
            cin >> fill_num;
            double_arr[i][j] = fill_num;
        }
    }

    Reverse(double_arr,rows, cols);
    
    for (int i = 0; i < rows;i++){
        for (int j = 0 ; j < cols;j++){
            cout << double_arr[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "FINISH";
    return 0; 
}*/
//Моя проблема была в том, что я раз 1) неправильно выбрал скобки, я не инициализировал размер массива, а сразу ставил его как пустой, и 2) я неправильно объявлял массив внутри массива, я ставил его как отдельный массив, а не как элемент, то есть как *double_arr не как double_arr[i]

// #include <iostream>
// #include <fstream>

// using namespace std;
// const short max_len = 256;

// bool isdigit(char c)
// {
//     return (c >= '0' && c <= '9');
// }

// bool isspace(char c)
// {
//     return (c == ' ');
// }

// bool issign(char c)
// {
//     return (c == '-' || c == '+');
// }

// bool isdot(char c)
// {
//     return (c == '.');
// }

// bool parse_number(const char* t) {
//     if (t == '\0') return false; // Empty string is not a number

//     bool has_digit = false;
//     bool has_dot = false;
//     bool has_sign = false;

//     // Check for optional sign at the beginning
//     if (issign(t)) {
//         has_sign = true;
//         t++; // Move to the next character
//     }

//     while (t) {
//         if (isdigit(t)) {
//             has_digit = true;
//         } else if (isdot(*t)) {
//             if (has_dot) return false; // More than one dot is not allowed
//             has_dot = true;
//         } else {
//             return false; // Invalid character
//         }
//         t++;
//     }

//     return has_digit; // There must be at least one digit
// }

// int main() {
//     char test1[] = "123";
//     char test2[] = "-45.67";
//     char test3[] = "+0.89";
//     char test4[] = "abc";
//     char test5[] = "12.34.56";

//     cout << parse_number(test1) << endl; // 1 (valid)
//     cout << parse_number(test2) << endl; // 1 (valid)
//     cout << parse_number(test3) << endl; // 1 (valid)
//     cout << parse_number(test4) << endl; // 0 (invalid)
//     cout << parse_number(test5) << endl; // 0 (invalid)

//     return 0;
// }


//ChatGpt Version
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

/*int main() {
    // Это входной файл, но из него мы берем значения, можно запутаться
    std::ifstream file_in("input.txt");
    if (!file_in) {
        std::cerr << "Ошибка открытия input.txt" << std::endl;
        return 1;
    }

    // Запомниаем, выходной файл ,в него записываем.
    std::ofstream file_out("output.txt");
    if (!file_out) {
        std::cerr << "Ошибка открытия output.txt" << std::endl;
        return 1;
    }

    int num1, num2;

    //Читаем оба числа из файла
    file_in >> num1 >> num2;

    int sum = num1 + num2;

    // Записываем результат в выходной файл
    file_out << sum;

    file_in.close();
    file_out.close();

    return 0;
}
*/

void processArray(std::vector<int>& numbers, std::ofstream& file_out) {
    for (int i = 0; i < numbers.size(); i++) {
        // Проверка для одиночной цифры
        if (i == 0 || numbers[i] != numbers[i - 1] + 1) {
            // Если цифра не равна предыдущей + 1, мы проверяем последовательность
            std::string sequence = std::to_string(numbers[i]);
            int j = i + 1;

            // Проверяем последующие числа
            while (j < numbers.size() && numbers[j] == numbers[j - 1] + 1) {
                sequence += " " + std::to_string(numbers[j]);
                j++;
            }

            // Если последовательность имеет длину больше 1, записываем в файл
            if (sequence.size() > 1) {
                file_out << sequence << std::endl;
            }

            // Устанавливаем индекс i на j, чтобы пропустить уже пройденные числа
            i = j - 1; 
        }
    }
}

int main() {
    std::ifstream file_in("input.txt");
    std::ofstream file_out("output.txt");

    if (!file_in) {
        std::cerr << "Ошибка открытия input.txt" << std::endl;
        return 1;
    }

    if (!file_out) {
        std::cerr << "Ошибка открытия output.txt" << std::endl;
        return 1;
    }

    // Читаем данные из файла
    std::vector<int> numbers;
    std::string line;
    
    if (std::getline(file_in, line)) {
        std::istringstream iss(line);
        int number;
        while (iss >> number) {
            numbers.push_back(number);
        }
    }

    // Обрабатываем массив
    processArray(numbers, file_out);

    // Закрываем файлы
    file_in.close();
    file_out.close();

    return 0;
}

// #include <iostream>
// #include <fstream>
// #include <cctype>
// #include <cstring>

// bool isNumber(char arr[]) 
// {
//     bool is_point = false;
//     bool digit = false;

//     // Чтобы отрицательные числа считывались в массив.
//     int start = 0;
//     if (arr[0] == '-') 
//     {
//         start = 1;
//     }

//     for (int i = start; i < strlen(arr); i++) 
//     {
//         if (isdigit(arr[i]))
//         {
//             digit = true;
//         } 
//         else if (arr[i] == '.') 
//         {
//             if (is_point) 
//             {
//                 return false; 
//             }
//             is_point = true;
//         } 
//         else 
//         {
//             digit = false; 
//         }
//     }

//     return digit;
// }

// //Функция ,чтобы найти произведение всех положительных квадратов
// void processArray(std::ofstream &file_out, double arr[], int size) {
//     double sqrt_mult = 1; //Храним произведение
//     bool positive = false; 

//     for (int i = 0; i < size; ++i) 
//     {
//         if (arr[i] > 0)
//         {
//             sqrt_mult *= (arr[i] * arr[i]); 
//             positive = true; 
//         }
//     }

//     if (!positive) 
//     {
//         sqrt_mult = 0; 
//     }

//     file_out << sqrt_mult;
// }

// int main() 
// {
//     int max_store = 10;

//     double *numbers = new double[max_store]; 
//     int count = 0;

//     std::ifstream file_in("input.txt");
//     if (!file_in) 
//     {
//         std::cerr << "Can't open input.txt, there might be errors!" << std::endl;
//         return 1;
//     }

//     char check_input[21];

//     while (file_in >> check_input) 
//     { 
//         // Записываем подходящие значения для массива
//         if (isNumber(check_input)) 
//         {
//             if (count >= max_store) 
//             {
//                 max_store *= 2;

//                 double *new_numbers = new double[max_store];
//                 for (int i = 0; i < count; i++) 
//                 {
//                     new_numbers[i] = numbers[i];
//                 }
//                 delete[] numbers;
//                 numbers = new_numbers;
//             }

//             numbers[count] = std::stof(check_input); 
//             count++;
//         } 
//         else 
//         {
//             std::cout << "Not numeric input: " << check_input << "\n";
//         }
//     }

//     std::ofstream file_out("output.txt");
//     if (!file_out) 
//     {
//         std::cerr << "Can't open output.txt there might be errors!" << std::endl;
//         return 1;
//     }

//     processArray(file_out, numbers, count);

//     file_in.close();
//     file_out.close();
//     delete[] numbers;

//     return 0;
// }