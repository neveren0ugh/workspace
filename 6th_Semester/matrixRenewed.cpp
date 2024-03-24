#include <iostream>
#include <vector>


enum ERROR
{
    SUCCES = 0,
    ERROR_SUMM = -1,
    ERROR_MULTI = -2,
    ERROR_POW = -3,
    ERROR_VECTINIT = -4,
    ERROR_INDEX = -5,
    ERROR_DIMENSION = -6
};

class Matrix
{
private:
    unsigned m_height;
    unsigned m_width;
    double** m_ptr = nullptr;
public:
    //Конструкторы и деструктор
    Matrix(const double _value);                                                //Матрица 1 на 1 со значением
    Matrix(const unsigned _height, const unsigned _width, const double _value);
    Matrix(const Matrix& _origin);                                           //Копия матрицы
    Matrix(const std::vector<std::vector<double>>& _vector);                   //Переварить вектор из векторов
    ~Matrix();
    //Полезные функции
    void fill(const double _value);                                             //Заполнить всю матрицу значением
    void print();
    void resize(const unsigned _height, const unsigned _width);
    void t();                                                                //Транспонировать
    void set(const unsigned _i, const unsigned _j, const double _value);        //Задать элемент вручную
    void addCol(const std::vector<double> _vector, const unsigned _j);
    void addRow(const std::vector<double> _vector, const unsigned _i);
    //Перегрузка привычных операторов
    friend Matrix operator +(const Matrix& _Lmatrix, const Matrix& _Rmatrix);
    friend Matrix operator -(const Matrix& _Lmatrix, const Matrix& _Rmatrix);
    friend Matrix operator *(const Matrix& _Lmatrix, const Matrix& _Rmatrix);
    friend Matrix pow(const Matrix& _matrix, const unsigned _degree);        //Возведение в положительную степень
    friend bool operator ==(const Matrix& _Lmatrix, const Matrix& _Rmatrix); //Проверка на поэлементное равенство
    double& operator ()(const unsigned _i, const unsigned _j);
    Matrix& operator =(const Matrix& _matrix);

    int getHeight();
    int getWidth();
    void identity();
    //Matrix translation(const Matrix _sourceCoord, const Matrix _transformedCoord);
};

Matrix::Matrix(const double _value = 0)
{
    m_ptr = new double*;
    m_height = 1;
    *m_ptr = new double;
    m_width = 1;
    **m_ptr = _value;
}

Matrix::Matrix(const unsigned _height, const unsigned _width, const double _value = 0)
{
    m_ptr = new double* [_height];
    m_height = _height;
    for (int i(0); i < m_height; i++)
    {
        m_ptr[i] = new double[_width];
    }
    m_width = _width;
    this->fill(_value);
}

Matrix::Matrix(const Matrix& _origin)
{
    m_height = _origin.m_height;
    m_width = _origin.m_width;
    double** tempo_ptr = new double* [m_height];
    for (int i(0); i < m_height; i++)
    {
        tempo_ptr[i] = new double[m_width];
        for (int j(0); j < m_width; j++)
        {
            tempo_ptr[i][j] = _origin.m_ptr[i][j];
        }
    }
    m_ptr = tempo_ptr;
}

Matrix::Matrix(const std::vector<std::vector<double>>& _vector)
{
    try
    {
        double size = _vector[0].size();
        for (int i(1); i < _vector.size(); i++)
        {
            if (_vector[i].size() != size)
            {
                throw(std::string{ "error: incorrect size of vector!\n" });
                exit(ERROR_VECTINIT);
            }
        }
        double** tempo_ptr = new double* [_vector.size()];
        for (int i(0); i < _vector.size(); i++)
        {
            tempo_ptr[i] = new double[size];
            for (int j(0); j < size; j++)
            {
                tempo_ptr[i][j] = _vector[i][j];
            }
        }
        m_height = _vector.size();
        m_width = size;
        m_ptr = tempo_ptr;

    }
    catch (const std::string _errorMessage)
    {
        std::cerr << _errorMessage;
        exit(ERROR_VECTINIT);
    }
}

Matrix::~Matrix()
{
    if ((m_height == 1) && (m_width == 1))
    {
        delete* m_ptr;
        delete m_ptr;
    }
    else
    {
        for (int i(0); i < m_height; i++)
        {
            delete[] m_ptr[i];
        }
        delete[]  m_ptr;
    }
}

//

void Matrix::fill(const double _value)
{
    for (int i(0); i < m_height; i++)
    {
        for (int j(0); j < m_width; j++)
        {
            this->set(i, j, _value);
        }
    }
}

void Matrix::print()
{
    for (int i(0); i < m_height; i++)
    {
        for (int j(0); j < m_width; j++)
        {
            std::cout << m_ptr[i][j];
            if (j != m_width - 1)
            {
                std::cout << '\t';
            }
        }
        std::cout << std::endl;
    }
}

void Matrix::resize(const unsigned _height, const unsigned _width)
{
    double** tempo_ptr = new double* [_height];
    for (int i(0); i < _height; i++)
    {
        tempo_ptr[i] = new double[_width];
        if (i < m_height)
        {
            for (int j(0); j < _width; j++)
            {
                if (j < m_width)
                {
                    tempo_ptr[i][j] = m_ptr[i][j];
                }
                else
                {
                    tempo_ptr[i][j] = 0;
                }
            }
        }
        else
        {
            for (int j(0); j < _width; j++)
            {
                tempo_ptr[i][j] = 0;
            }
        }
    }
    this->~Matrix();
    m_ptr = tempo_ptr;
    m_height = _height;
    m_width = _width;
}

void Matrix::t()
{
    double** tempo_ptr = new double* [m_width];
    for (int i(0); i < m_width; i++)
    {
        tempo_ptr[i] = new double[m_height];
        for (int j(0); j < m_height; j++)
        {
            tempo_ptr[i][j] = m_ptr[j][i];
        }
    }
    this->~Matrix();
    m_ptr = tempo_ptr;
    int tempo_height(m_height);
    m_height = m_width;
    m_width = tempo_height;
}

void Matrix::set(const unsigned _i, const unsigned _j, const double _value)
{
    m_ptr[_i][_j] = _value;
}

void Matrix::addCol(const std::vector<double> _vector, const unsigned _j = 0)
{
    try
    {
        if (_vector.size() != m_height)
        {
            throw(std::string{ "error: incorrect size of vector!\n" });
        }
        if (_j > m_width)
        {
            throw(std::string{ "error: incorrect index!\n" });
        }
        this->resize(m_height, m_width + 1);
        for (int j(m_width - 1); j >= 0; j--)
        {
            for (int i(0); i < m_height; i++)
            {
                if (j > _j)
                {
                    m_ptr[i][j] = m_ptr[i][j - 1];
                }
                else if (j == _j)
                {
                    m_ptr[i][j] = _vector[i];
                }
            }
        }
    }
    catch (std::string _errorMessage)
    {
        std::cerr << _errorMessage;
        exit(ERROR_VECTINIT);
    }
}

void Matrix::addRow(const std::vector<double> _vector, const unsigned _i = 0)
{
    try
    {
        if (_vector.size() != m_width)
        {
            throw(std::string{ "error: incorrect size of vector!\n" });
        }
        if (_i > m_height)
        {
            throw(std::string{ "error: incorrect index!\n" });
        }
        this->resize(m_height + 1, m_width);
        for (int i(m_height - 1); i >= 0; i--)
        {
            for (int j(0); j < m_width; j++)
            {
                if (i > _i)
                {
                    m_ptr[i][j] = m_ptr[i - 1][j];
                }
                else if (i == _i)
                {
                    m_ptr[i][j] = _vector[j];
                }
            }
        }
    }
    catch (std::string _errorMessage)
    {
        std::cerr << _errorMessage;
        exit(ERROR_VECTINIT);
    }
}

//

Matrix operator +(const Matrix& _Lmatrix, const Matrix& _Rmatrix)
{
    try
    {
        if ((_Lmatrix.m_height == _Rmatrix.m_height) && (_Lmatrix.m_width == _Rmatrix.m_width))
        {
            Matrix tempo(_Lmatrix.m_height, _Lmatrix.m_width);
            for (int i(0); i < tempo.m_height; i++)
            {
                for (int j(0); j < tempo.m_width; j++)
                {
                    tempo.set(i, j, _Lmatrix.m_ptr[i][j] + _Rmatrix.m_ptr[i][j]);
                }
            }
            return tempo;
        }
        else
        {
            throw std::string{ "error: Can not do such operation with different sized matrices!\n" };
        }
    }
    catch (const std::string _errorMessage)
    {
        std::cerr << _errorMessage;
        exit(ERROR_SUMM);
    }
}

Matrix operator -(const Matrix& _Lmatrix, const Matrix& _Rmatrix)
{
    try
    {
        if ((_Lmatrix.m_height == _Rmatrix.m_height) && (_Lmatrix.m_width == _Rmatrix.m_width))
        {
            Matrix tempo(_Lmatrix.m_height, _Lmatrix.m_width);
            for (int i(0); i < tempo.m_height; i++)
            {
                for (int j(0); j < tempo.m_width; j++)
                {
                    tempo.set(i, j, _Lmatrix.m_ptr[i][j] - _Rmatrix.m_ptr[i][j]);
                }
            }
            return tempo;
        }
        else
        {
            throw std::string{ "error: Can not do such operation with different sized matrices!\n" };
        }
    }
    catch (const std::string _errorMessage)
    {
        std::cerr << _errorMessage;
        exit(ERROR_SUMM);
    }
}

Matrix operator *(const Matrix& _Lmatrix, const Matrix& _Rmatrix)
{
    try
    {
        if (_Lmatrix.m_width == _Rmatrix.m_height)
        {
            Matrix tempo(_Lmatrix.m_height, _Rmatrix.m_width);
            for (int i(0); i < tempo.m_height; i++)
            {
                for (int j(0); j < tempo.m_width; j++)
                {
                    for (int k(0); k < _Lmatrix.m_width; k++)
                    {
                        tempo.m_ptr[i][j] += _Lmatrix.m_ptr[i][k] * _Rmatrix.m_ptr[k][j];
                    }
                }
            }
            return tempo;
        }
        else
        {
            throw std::string{ "error: Can not multiply matrices with such dimensions!\n" };
        }
    }
    catch (const std::string _errorMessage)
    {
        std::cerr << _errorMessage;
        exit(ERROR_MULTI);
    }
}

Matrix pow(const Matrix& _matrix, const unsigned _degree)
{
    try
    {
        if (_degree > 0)
        {
            int i(1);
            Matrix tempo(_matrix);
            while (i < _degree)
            {
                tempo = tempo * tempo;
                i++;
            }
            return tempo;
        }
        else
        {
            throw std::string{ "error: Incorrect argument for function 'pow'\n" };
        }
    }
    catch (const std::string _errorMessage)
    {
        std::cerr << _errorMessage;
        exit(ERROR_POW);
    }
}

bool operator ==(const Matrix& _Lmatrix, const Matrix& _Rmatrix)
{
    bool signal = true;
    if ((_Lmatrix.m_height == _Rmatrix.m_height) && (_Lmatrix.m_width == _Rmatrix.m_width))
    {
        for (int i(0); i < _Lmatrix.m_height; i++)
        {
            for (int j(0); j < _Lmatrix.m_width; j++)
            {
                if (_Lmatrix.m_ptr[i][j] != _Rmatrix.m_ptr[i][j])
                {
                    signal = false;
                    return signal;
                }
            }
        }
    }
    else
    {
        signal = false;
        return signal;
    }
}

double& Matrix::operator ()(const unsigned _i, const unsigned _j)
{
    return m_ptr[_i][_j];
}

Matrix& Matrix::operator =(const Matrix& _matrix)
{
    this->resize(_matrix.m_height, _matrix.m_width);
    for (int i(0); i < m_height; i++)
    {
        for (int j(0); j < m_width; j++)
        {
            this->set(i, j, _matrix.m_ptr[i][j]);
        }
    }
    return *this;
}

void Matrix::identity()
{
    if (m_height != m_width)
    {
        std::cerr << "Can't turn non-square matrix into identity" << std::endl;
        exit(ERROR_DIMENSION);
    }
    for (int i(0); i < m_height; i++)
    {   
        for (int j(0); j < m_height; j++)
        {
            if (i == j)
                this->set(i, j, 1);
            else
                this->set(i, j, 0);
        }
    }
};

int Matrix::getHeight()
{
    return m_height;
}
int Matrix::getWidth()
{
    return m_width;
}



Matrix* translation(Matrix _sourceCoord, Matrix _transformedCoord) 
{
    if ((_sourceCoord.getHeight() != _transformedCoord.getHeight()) or (_sourceCoord.getWidth() != _transformedCoord.getWidth()))
    {
        std::cerr << "Unable to transform coordinates with different dimension sizes" << std::endl;
        exit(ERROR_DIMENSION);
    }
    if ((_sourceCoord.getWidth() != 1) or (_transformedCoord.getWidth() != 1))
    {
        std::cerr << "Sorce data does not represent coordinate vector" << std::endl;
        exit(ERROR_DIMENSION);
    }

    Matrix *tempo = new Matrix(_sourceCoord.getHeight(), _sourceCoord.getHeight(), 0);
    double _toApply;
    tempo->identity();
    for (int j(0); j < _sourceCoord.getHeight(); j++)
    {   
        _toApply = _transformedCoord(j, _transformedCoord.getWidth() - 1);
        _toApply -= _sourceCoord(j, _sourceCoord.getWidth() - 1);
        _toApply /= _sourceCoord(j, _sourceCoord.getWidth() - 1);
        tempo->set(j, _sourceCoord.getHeight() - 1, _toApply);
    }
    tempo->set(_sourceCoord.getHeight() - 1, _sourceCoord.getHeight() - 1, 1);
    return tempo;
};

int main()
{
    ////Объект класса можно объявить, передавая только одно значение. Создастся матрица 1 на 1 с этим значением (по умолчанию значение 0)
    //{
    //    Matrix A(1);
    //    std::cout << "Вызов Matrix A(1):\n";
    //    A.print();
    //    std::cout << std::endl;
    //}
    ////Можно передать размеры матрицы и значение. Тогда создастся матрица соответствующего размера с этим значением (по умолчанию значение 0)
    //{
    //    Matrix A(2, 3, 1);
    //    std::cout << "Вызов Matrix A(2, 3, 1):\n";
    //    A.print();
    //    std::cout << std::endl;
    //}
    ////Можно задать элементы матрицы вручную
    //{
    //    Matrix A({
    //                    {1, 2, 3},
    //                    {4, 5, 6}
    //        });
    //    std::cout << "Вызов Matrix A({ {1, 2, 3}, {4, 5, 6} }):\n";
    //    A.print();
    //    std::cout << std::endl;

    //    //Можно скопировать готовую матрицу

    //    Matrix B(A);
    //    std::cout << "Вызов Matrix B(A):\n";
    //    B.print();
    //    std::cout << std::endl;

    //    //Готовую матрицу можно принудительно заполнить заданным числом

    //    B.fill(7);
    //    std::cout << "Вызов B.fill(7):\n";
    //    B.print();
    //    std::cout << std::endl;

    //    //Можно увеличить размеры матрицы, передавая требуемые параметры

    //    B.resize(3, 4);
    //    std::cout << "Вызов B.resize(3, 4):\n";
    //    B.print();
    //    std::cout << std::endl;

    //    //Можно и уменьшить размеры

    //    B.resize(3, 2);
    //    std::cout << "Вызов B.resize(3, 2):\n";
    //    B.print();
    //    std::cout << std::endl;

    //    //Можно транспонировать матрицу

    //    B.t();
    //    std::cout << "Вызов B.t():\n";
    //    B.print();
    //    std::cout << std::endl;

    //    //Можно вписать в матрицу вектор-столбец, передавая сам вектор и желаемую позицию (по умолчанию на первое место)

    //    B.addCol({ 1, 2 }, 1);
    //    std::cout << "Вызов B.addCol({1, 2}, 1):\n";
    //    B.print();
    //    std::cout << std::endl;

    //    //Можно вписать в матрицу вектор-строку, передавая сам вектор и желаемую позицию (по умолчанию на первое место)

    //    B.addRow({ 5, 5, 5, 5 }, 1);
    //    std::cout << "Вызов B.addRow({5, 5, 5, 5}, 1):\n";
    //    B.print();
    //    std::cout << std::endl;
    //}
    ////Можно складывать матрицы
    //{
    //    Matrix A({
    //                    {1, 2},
    //                    {3, 4}
    //        });
    //    std::cout << "Вызов Matrix A({ {1, 2}, {3, 4} }):\n";
    //    A.print();
    //    std::cout << std::endl;
    //    Matrix B({
    //                    {5, 6},
    //                    {7, 8}
    //        });
    //    std::cout << "Вызов Matrix B({ {5, 6}, {7, 8} }):\n";
    //    B.print();
    //    std::cout << std::endl;
    //    {
    //        Matrix C(A + B);
    //        std::cout << "Вызов Matrix C(A + B):\n";
    //        C.print();
    //        std::cout << std::endl;
    //    }
    //    //Можно вычетать матрицы
    //    {
    //        Matrix C(A - B);
    //        std::cout << "Вызов Matrix C(A - B):\n";
    //        C.print();
    //        std::cout << std::endl;
    //    }
    //    //Можно перемножать матрицы
    //    {
    //        Matrix C(A * B);
    //        std::cout << "Вызов Matrix C(A*B):\n";
    //        C.print();
    //        std::cout << std::endl;
    //    }
    //    //Можно возвести матрицу в степень
    //    {
    //        Matrix C(pow(A, 2));
    //        std::cout << "Вызов Matrix C(pow(A, 2)):\n";
    //        C.print();
    //        std::cout << std::endl;
    //    }
    //    //Можно проверить матрицы на поэлементное соответствие

    //    std::cout << "Вызов A == B:\n";
    //    std::cout << (bool)(A == B) << std::endl;
    //    std::cout << std::endl;

    //    //Можно присвоить матрице значение другой матрицы
    //    B = A;
    //    std::cout << "Вызов B = A:\n";
    //    std::cout << "Вызов B:\n";
    //    B.print();
    //    std::cout << std::endl;

    //    //Можно обращаться к элементам матрицы напрямую

    //    std::cout << "Вызов A(0, 1):\n";
    //    std::cout << A(0, 1) << std::endl;
    //    std::cout << std::endl;

    //    //Можно изменить значение элемента

    //    A(0, 1) = -1;
    //    std::cout << "Вызов A(0, 1) = -1:\n";
    //    std::cout << "Вызов A(0, 1):\n";
    //    std::cout << A(0, 1) << std::endl;
    //    std::cout << std::endl;


    // }
    

    /*Matrix first({
                    {2},
                    {1.5},
                    {8},
                    {2}
        });
    Matrix second({
                    {3},
                    {4},
                    {5},
                    {1}
        });*/
    Matrix first(4, 1, 6);
    Matrix second(4, 1, 4);
    second(1, 0) = 13;
    second(2, 0) = 11;
    Matrix * A = new Matrix(4, 4, 0);
    A = translation(first, second);
    A->print();
    std::cout << std::endl;
    //Matrix third(5, 1, 16);
    //A = translation(first, third); //Ошибка размерностей исходных векторов
    //std::cout << std::endl;
    //Matrix fourth(4, 2, 0);
    //Matrix fifth(4, 2, 1);
    //A = translation(fifth, fourth); //Ошибка вводных условий - введенные данные не являются вектором координат
    //std::cout << std::endl;
    Matrix multidim1({
                    {2},
                    {1.5},
                    {8},
                    {141},
                    {1}
        });
    Matrix multidim2({
                    {3},
                    {4},
                    {5},
                    
                    {1}
        });
    A = translation(multidim1, multidim2);
    A->print();
    return SUCCES;
}