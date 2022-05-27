#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream> 
#include <assert.h>
#include <algorithm>

using namespace std;

template <class T>
class LinkList;
class DocInfo;
class TermInfo;
class SearchEngine;

string ToUpper(string word)
{
	for_each(word.begin(), word.end(), [](char& c) {
		c = ::toupper(c);
		});
	return word;
}

template <class T>
class Node {
private:
	T data;
	Node<T>* next;
	Node<T>* pre;
	friend LinkList<T>;
public:
	Node()
	{
		next = nullptr;
		pre = nullptr;
	}

	Node(T element)
	{
		data = element;
		next = nullptr;
		pre = nullptr;
	}

	~Node()
	{
		next = nullptr;
		pre = nullptr;
	}
};

template <class T>
class LinkList {
private:
	Node<T>* head;
	Node<T>* tail;
	int size;
	friend DocInfo;
public:
	class Iterator
	{
	private:
		Node<T>* curr;
		friend class LinkList<T>;
	public:
		Iterator()
		{
			curr = nullptr;
		}

		Iterator(Iterator const& that)
		{
			this->curr = that.curr;
		}

		Iterator(LinkList<T> const& list)
		{
			curr = list.head;
		}

		T& operator*()
		{
			assert(this->curr != nullptr);
			return this->curr->data;
		}

		bool operator!=(Iterator const& that)const
		{
			return (this->curr != that.curr);

		}

		bool operator==(Iterator const& that) const
		{
			return (this->curr == that.curr);
		}

		Iterator& operator++()
		{
			assert(this->curr != nullptr);
			this->curr = curr->next;
			return *this;
		}

		Iterator& operator++(int)
		{
			assert(this->curr != nullptr);
			Iterator newIterator(*this);
			this->curr = curr->next;
			return newIterator;
		}

		Iterator& operator=(Iterator const& that)
		{
			assert(this->curr != nullptr);
			this->curr = that->curr;
		}

		Iterator& operator--()
		{
			assert(this->curr != nullptr || this->curr != head);
			this->curr = curr->pre;
			return *this;
		}

	};

	typename Iterator begin()
	{
		Iterator it(*this);
		return it;
	}

	typename Iterator end()
	{
		Iterator it;
		it.curr = nullptr;
		return it;

	}

	LinkList()
	{
		head = nullptr;
		tail = nullptr;
		size = 0;
	}

	void insertAtStart(T const& element)
	{
		if (head == nullptr)
		{
			head = new Node<T>(element);
			tail = head;
		}
		else
		{
			Node<T>* temp = new Node<T>(element);
			temp->next = head;
			head->pre = temp;
			head = temp;
		}
		size++;
	}

	void insertAtEnd(T const& element)
	{
		if (head == nullptr)
		{
			head = new Node<T>(element);
			tail = head;
		}
		else
		{
			tail->next = new Node<T>(element);
			tail->next->pre = tail;
			tail = tail->next;
		}
		size++;
	}

	int getSize()
	{
		return size;
	}

	void print() const
	{
		cout << "List has following Data: " << endl;
		Node<T>* temp = head;
		while (temp != nullptr)
		{
			cout << temp->data;
			temp = temp->next;
		}
		cout << endl;
	}

	bool search(T const& element)
	{
		if (isEmpty() == true)
		{
			cout << "List is Empty.\nSo it has no Element!" << endl;
			return false;
		}
		else
		{
			Node<T>* temp = head;
			while (temp != nullptr)
			{
				if (temp->data == element)
					return true;
				temp = temp->next;
			}
			return false;
		}

	}

	T search(T const& element, int dummy)
	{
		Node<T>* temp = head;
		while (temp != nullptr)
		{
			if (temp->data == element)
				return temp->data;
			temp = temp->next;
		}
	}

	void Search_Replace(T const& element)
	{
		Node<T>* temp = head;
		while (temp != nullptr)
		{
			if (temp->data == element)
			{
				temp->data = element;
			}
			temp = temp->next;
		}
	}

	void operator=(LinkList<T>* obj)
	{
		this->DeleteAll();
		while (obj->head != nullptr)
		{
			this->insertAtEnd(obj->head->data);
			obj->head = obj->head->next;
		}
	}

	void operator=(LinkList<T> obj)
	{
		this->DeleteAll();
		while (obj.head != nullptr)
		{
			this->insertAtEnd(obj.head->data);
			obj.head = obj.head->next;
		}


	}

	void DeleteAll()
	{
		Node<T>* temp;
		temp = head;
		while (head != nullptr)
		{
			temp = head->next;
			delete head;
			head = temp;
		}
		head = tail = nullptr;
	}

	bool isEmpty()
	{
		if (head == nullptr)
			return true;
		return false;
	}

	bool SearchDuplicates(T const value)
	{
		int count = 0;
		Node<T>* temp = head;
		while (temp != nullptr)
		{
			if (temp->data == value)
			{
				count++;
			}
			temp = temp->next;
		}
		if (count >= 2)
			return true;
		else
			return false;

	}

	void removeDuplicates()
	{
		if (isEmpty() == true)
		{
			cout << "List is Empty." << endl;
		}
		else
		{
			Node<T>* temp = head;
			while (temp != nullptr)
			{
				if (SearchDuplicates(temp->data) == true)
				{
					int value = temp->data;
					Node<T>* current = head;
					while (current->next != nullptr)
					{
						bool flag = false;
						if (current->next->data == value)
						{
							Node <T>* temp2;
							temp2 = current->next;
							current->next = temp2->next;
							delete temp2;
							flag = true;
							size--;
						}
						if (!flag)
						{
							current = current->next;
						}
					}

				}
				temp = temp->next;
			}
		}

	}

	~LinkList()
	{
		Node<T>* temp;
		temp = head;
		while (head != nullptr)
		{
			temp = head->next;
			delete head;
			head = temp;
		}
		head = tail = nullptr;
	}
};

class DocInfo
{
private:
	string DocID;
	int frequency;
	friend SearchEngine;
	friend ostream& operator<<(ostream& out, DocInfo& obj);
public:
	DocInfo()
	{
		DocID = "";
		frequency = 0;
	}

	DocInfo(string ID, int f = 1)
	{
		DocID = ID;
		frequency = f;
	}

	DocInfo(DocInfo const& obj)
	{
		this->DocID = obj.DocID;
		this->frequency = obj.frequency;
	}

	DocInfo(DocInfo* const& obj)
	{
		this->DocID = obj->DocID;
		this->frequency = obj->frequency;
	}

	bool operator==(const DocInfo* data)
	{
		return (this->DocID == data->DocID) ? 1 : 0;
	}

	bool operator==(const DocInfo data)
	{
		return (this->DocID == data.DocID) ? 1 : 0;
	}

	void operator=(const DocInfo* data)
	{
		this->DocID = data->DocID;
		this->frequency = data->frequency;
	}

	void operator=(DocInfo data)
	{
		this->DocID = data.DocID;
		this->frequency = data.frequency;
	}
};

ostream& operator<<(ostream& out, DocInfo& obj) {
	out << obj.DocID << endl;
	out << obj.frequency << endl;
	return out;
}

class TermInfo
{
private:
	friend DocInfo;
	friend SearchEngine;
	string key;
	LinkList<DocInfo> Doc;

public:
	TermInfo()
	{
		key = "";
	}

	bool operator==(TermInfo* data)
	{
		return (this->key == data->key) ? 1 : 0;
	}

	bool operator==(TermInfo data)
	{
		return (this->key == data.key) ? 1 : 0;
	}

	void operator=(TermInfo* data)
	{
		this->key = data->key;
		this->Doc = data->Doc;
	}

	void operator=(TermInfo data)
	{
		this->key = data.key;
		this->Doc = data.Doc;
	}

	~TermInfo()
	{ }
};

class SearchEngine
{
	friend DocInfo;
	friend TermInfo;
private:
	TermInfo* index;
	int currS;
	int maxS;
	int total;

public:
	SearchEngine()
	{
		index = nullptr;
		currS = maxS = total = 0;
	}

	int IsNamePreset(string key)
	{
		for (int i = 0; i < currS; i++)
		{
			if (index[i].key == key)
				return i;
		}
		return -1;
	}

	int IsDocPresent(DocInfo doc[], string name, int size)
	{
		for (int i = 0; i < size; i++)
		{
			if (doc[i].DocID == name)
				return i;
		}
		return -1;
	}

	void InsertInIndex(string k, string DocName)
	{
		if (maxS == 0)
		{
			index = new TermInfo[1];
			currS = maxS = 1;
			index[0].key = k;
			DocInfo* obj = new DocInfo(DocName, 1);
			index[0].Doc.insertAtEnd(obj);
		}
		else if (currS < maxS)
		{
			int repeat = IsNamePreset(k);
			if (repeat > -1)
			{
				DocInfo obj(DocName, 1);
				if (index[repeat].Doc.search(obj))
				{
					obj = index[repeat].Doc.search(obj, 1);
					obj.frequency++;
					index[repeat].Doc.Search_Replace(obj);
				}
				else
				{
					DocInfo* obj = new DocInfo(DocName, 1);
					index[repeat].Doc.insertAtEnd(obj);
				}
			}
			else
			{
				index[currS].key = k;
				DocInfo* obj = new DocInfo(DocName, 1);
				index[currS].Doc.insertAtEnd(obj);
				currS++;

			}
		}
		else if (currS == maxS)
		{
			int repeat = IsNamePreset(k);
			if (repeat > -1)
			{
				DocInfo obj(DocName, 1);
				if (index[repeat].Doc.search(obj))
				{
					obj = index[repeat].Doc.search(obj, 1);
					obj.frequency++;
					index[repeat].Doc.Search_Replace(obj);
				}
				else
				{
					DocInfo* obj = new DocInfo(DocName, 1);
					index[repeat].Doc.insertAtEnd(obj);
				}
			}
			else
			{
				TermInfo* temp = new TermInfo[2 * maxS];
				for (int i = 0; i < maxS; i++)
				{
					temp[i] = index[i];
				}
				//delete[] index;
				//index=nullptr;
				index = temp;
				DocInfo* obj = new DocInfo(DocName, 1);
				index[currS].key = k;
				index[currS].Doc.insertAtEnd(obj);
				currS++;
				maxS *= 2;
			}
		}

	}

	void CreateIndex(string docs[], int n)
	{
		ifstream read;
		string temp;
		for (int i = 0; i < n; i++)
		{
			read.open(docs[i]);
			if (read)
			{
				total++;
				while (read >> temp)
				{
					temp = ToUpper(temp);
					InsertInIndex(temp, docs[i]);
				}
				read.close();
			}
			else
			{
				cout << docs[i] << " is not present in directory" << endl;
			}
		}
	}

	void WordExtraction(string str)
	{
		LinkList<string> words;
		// word variable is storing a word 
		string word;

		// making a string stream 
		stringstream iss(str);

		// Read and print each word. 
		while (iss >> word)
			words.insertAtEnd(word);

		words.print();
	}

	void Search_Word(string word, DocInfo obj[], int& size)
	{
		int found = IsNamePreset(word);
		if (found > -1)
		{
			int count = 0;
			LinkList<DocInfo>::Iterator itr = index[found].Doc.begin();
			while (itr != index[found].Doc.end())
			{
				DocInfo temp = *itr;
				int docF = IsDocPresent(obj, temp.DocID, size);
				if (docF > -1)
				{
					obj[docF].frequency += temp.frequency;
				}
				else
				{
					obj[size] = temp;
					size++;
				}
				itr++;
			}
		}
	}

	void Search_Document(string find)
	{
		// word variable to store word 
		string word;

		int count = 0;
		// making a string stream 
		stringstream s(find);

		while (s >> word)
			count++;

		string* words = new string[count];

		int counter = 0;
		// Read and print each word. 
		stringstream iss(find);
		while (iss >> word || counter < count)
		{
			word = ToUpper(word);
			words[counter++] = word;
		}

		DocInfo* obj = new DocInfo[total];
		int curr = 0;

		for (int i = 0; i < count; i++)
		{
			Search_Word(words[i], obj, curr);
		}

		cout << "Documents containig given words are: " << endl;
		for (int i = 0; i < curr; i++)
		{
			cout << obj[i] << endl;
		}

	}

	void Add_Doc_To_Index(string fileName)
	{
		ifstream read;
		string temp;
		total++;
		read.open(fileName);
		if (read)
		{
			while (read >> temp)
			{
				InsertInIndex(temp, fileName);
			}
			read.close();
		}
		else
		{
			cout << fileName << " is not present in directory" << endl;
		}
	}

	void Print()
	{
		for (int i = 0; i < currS; i++)
		{
			cout << index[i].key << endl;
			index[i].Doc.print();
		}
	}

	~SearchEngine()
	{
		if (index != nullptr)
		{
			delete[] index;
		}
		index = nullptr;
	}
};

int main()
{
	string filename[5] = { "Doc1.txt", "Doc2.txt", "Doc3.txt", "Doc4.txt,Doc5.txt" };
	int n = 5;
	string find;
	cout << "Enter the word/s you want to find: " << endl;
	getline(cin, find);
	SearchEngine MyEngine;
	MyEngine.CreateIndex(filename, n);
	MyEngine.Print();
	MyEngine.Search_Document(find);

	system("pause");

	return 0;
}
