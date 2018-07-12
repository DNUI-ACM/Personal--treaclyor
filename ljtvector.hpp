#ifndef _VECTOR_TREACLYOR__
#define _VECTOR_TREACLYOR__
#include<stdio.h>
template < typename T>
class vector
{
public:
 using iterator = T*;
 using const_iterator = const T*;
 using size_type = size_t;//下标类型
 using reference = T&;
 using const_reference = const T&;
 using pointer = T*;
 using value_type = T;//迭代器所指对象的型别
 using const_pointer = const pointer;
class reverse_iterator//定义逆迭代器
{
private:
T * t;
public:
reverse_iterator(T *_t = nullptr) : t(_t){} //nullptr = 0
bool operator !=(const reverse_iterator & it)const
{
return t != it.t;
}
bool operator ==(const reverse_iterator & it)const
{
return t == it.t;
}
T operator *()
{
return *t;
}
reverse_iterator operator ++()//反向迭代器++等于正向迭代器--操作
{
return --t;
}
reverse_iterator operator ++(int)
{
T * p = t;
--t;
return p;
}
reverse_iterator operator --()//反向迭代器--操作等于正向迭代器++操作
{
return ++t;
}
reverse_iterator operator --(int)
{
T *p = t;
++t;
return p;
}
};
using const_reverse_iterator = const reverse_iterator;
private:
size_type len;//长度
size_type _capacity;//容量
T * data;
public:
iterator at(int i)//返回第几个元素
{
if(i >= len || i < 0)
return 0;
return data[i];
}
iterator insert(iterator it,int x)//在指定位置插入元素
{
iterator i = it;
if(len == _capacity)//如果满了，扩容
{
_capacity *= 2 + 1;
T * newp = data;
T * newdata = new T[_capacity];
for(i = _capacity/2; i >= 0; --i)
  newdata[i] = data[i-1];
  data = newdata;
  delete newp;
}
else
{
  for(iterator j = len; j >= it; --j)
    data[j] = data[j-1];
}
data[it] = x;
}
T& operator[](size_type position)//返回一个指向n位置的元素的引用
{
return data[position];
}
size_type size()//返回有多少个元素
{
return len;
}
size_type capacity()//返回容积
{
return _capacity;
}
void reserve(size_type number)//预留空间
{
if(number < _capacity)
return ;
size_type newcapacity = _capacity;
_capacity = number;
T * newp = data;
T * newdata = new T[_capacity];
for(size_type i = 0; i < newcapacity; ++i)
newdata[i] = data[i];
data = newdata;
delete newp;
}
void resize(size_type number)//重新分配大小
{
if(number <= len)
{
len = number;
reserve(2 * number);
return ;
}
reserve(2 * number);
len = number;
}
~vector()
{
  delete[] data;
}
vector()
{
len = 0;
_capacity = 4;
data = new T[_capacity];
}
vector(size_type number)
{
len = number;
_capacity = 2 * number;
data = new T[_capacity];
}
vector(size_type number, T t)//储存number个t元素
{
len = number;
_capacity = 2 * number;
data = new T[_capacity];
for(size_type i = 0; i < number; ++i)
data[i] = t;
}
vector(const vector &v)//将v里的元素拷贝到另一个vector里
{
len = v.len;
_capacity = v._capacity;
data = new T[_capacity];
for(size_type i = 0; i < _capacity; ++i)
data[i] = v.data[i];
}
void push_back(const iterator i)//在后部插入元素
{
data[len++] = *i;
if(len == _capacity)//如果满了，扩容
{
_capacity *= 2 + 1;
T * newp = data;
T * newdata = new T[_capacity];
for(size_type i = 0;i < _capacity/2; ++i)
{
newdata[i] = data[i];
}
data = newdata;
delete newp;
}
}
void pop_back()//删除后面元素
{
if(len == 0)
return ;
len--;
}
iterator erase(iterator it)
{
if(len == 0)
return 0;
len--;
for(iterator i = it; i != end(); ++i)
*i = *(i+1);
return it;
}
iterator erase(size_type position)//删除此位置元素
{
if(len == 0)
return 0;
len--;
for(size_type i = position; i < len; ++i)
data[i] = data[i+1];
return begin() + position;
}
iterator begin()//返回第一个位置
{
return data;
}
const_iterator begin()const
{
  return data;
}
iterator end()//返回最后一个位置的下一个位置
{
return data + len;
}
const_iterator end()const
{
  return data + len;
}
const_iterator cbegin()
{
return data;
}
const_iterator cend()//返回到开头
{
return data + len;
}
reverse_iterator rbegin()//返回最后一个元素
{
return data + len - 1;
}
const_reverse_iterator rbegin()const
{
  return data + len - 1;
}
reverse_iterator rend()//返回第一个元素的前一个位置
{
return data - 1;
}
const_reverse_iterator rend()const
{
  return data - 1;
}
const_reverse_iterator crbegin()
{
return data + len -1;
}
const_reverse_iterator crend()
{
return data - 1;
}
bool empty()//判断是否为空
{
return len == 0;
}
void clear()//清空操作
{
while(len)
pop_back();
}
void swap(vector & v)//交换
{
pointer temp_data = data;
data = v.data;
v.data = temp_data;
size_type temp_len = len;
len = v.len;
v.len = temp_len;
size_type temp_capacity = _capacity;
_capacity = v._capacity;
v._capacity = temp_capacity;
}
void assign(size_type number, reference value)//将区间内更替成这个值
{
if(len < number)
{
size_type i = 0;
for(i = 0; i < len; ++i)
data[i] = value;
for(;i < number; ++i)
push_back(value);
}
else
{
len = number;
for(size_type i = 0; i < len; ++i)
data[i] = value;
}
}
reference front()
{
  return *begin();
}
const_reference front()const
{
  return *begin();
}
reference back()
{
  return *(end() - 1);
}
const_reference back()const
{
  return *(end() - 1);
}
};
#endif