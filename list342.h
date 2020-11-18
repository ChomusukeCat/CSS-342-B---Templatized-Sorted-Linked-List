/*
 * CSS 342 B
 * List342 is a class for a fully ordered list, different types of objects can be stored in it.
 * Steven Chau
 * November 10, 2020
 */
#ifndef LIST342_H
#define LIST342_H
#include <string>
#include <fstream>
#include <iostream>
using namespace std;
template<class ItemType>
class List342
{
public:
	List342();
	List342(const List342& list);
	~List342();

	bool BuildList(string fileName);
	bool Insert(ItemType* obj);
	bool Remove(ItemType target, ItemType& result);
	bool Peek(ItemType target, ItemType& result) const;
	bool isEmpty() const;
	void DeleteList();
	bool Merge(List342& list1);
	friend ostream& operator<<(ostream& out_stream, const List342& list)
	{
		if (list.head_ == nullptr)
		{
			out_stream << "Empty List";
			return out_stream;
		}
		Node* curr;
		curr = list.head_;
		while (curr != nullptr)
		{
			ItemType temp = *(curr->data);
			out_stream << temp;
			curr = curr->next;
		}
		return out_stream;
	}
	List342 operator+(const List342& rhs) const;
	List342 operator+=(const List342& rhs);
	bool operator==(const List342& list) const;
	bool operator!=(const List342& list) const;
	List342& operator=(const List342& rhs);

private:
struct Node
{
	ItemType* data = nullptr;
	Node* next = nullptr;
};
Node* head_ = nullptr;
};

//implementation of functions

template<class ItemType>
List342<ItemType>::List342()
{

}

template<class ItemType>
List342<ItemType>::List342(const List342& list)
{
	*this = list;
}

template<class ItemType>
List342<ItemType>:: ~List342()
{
	this->DeleteList();
}

template<class ItemType>
bool List342<ItemType>::BuildList(string fileName)
{
	ifstream in_file(fileName);
	if (in_file) 
	{
		cout << "File: " << fileName << " found" << endl;
		while (!in_file.eof())
		{
			ItemType*item = new ItemType;
			in_file >> *item;
			this->Insert(item);
		}
		in_file.close();
		return true;
	}
	else
	{
		cout << "File: " << fileName << " not found" << endl;
		return false;
	}
}

template<class ItemType>
bool List342<ItemType>::isEmpty() const
{
	if (head_ == nullptr)
	{
		return true;
	}
	return false;
}

template<class ItemType>
bool List342<ItemType>::Merge(List342& list1)
{

	if (*this == list1)
	{
		return false;
	}
	Node* current = head_;
	//traverse both lists
	while (list1.head_ != nullptr && current != nullptr)
	{
		//if this next node is null
		if (current->next == nullptr)
		{
			current->next = list1.head_;
			list1.head_ = nullptr;
			return true;
		}
		//if both curr are equal, delete list1 duplicate node and set curr to next
		else if (*head_->data == *list1.head_->data)
		{
			Node* temp = list1.head_;
			list1.head_ = list1.head_->next;
			delete temp; //delete duplicate
			temp = nullptr;
		}
		//if this curr val is greater than list1 curr val, set this curr to list1 curr, move prev.curr back
		else if (*head_->data > *list1.head_->data)
		{
			head_ = list1.head_;
			list1.head_ = list1.head_->next;
			head_->next = current;
			current = head_;
		}
		//if this next val is the same as list1 curr val, delete duplicate
		else if (*current->next->data == *list1.head_->data)
		{
			Node* temp = current->next;
			temp = list1.head_;
			list1.head_ = list1.head_->next;
			delete temp;
			temp = nullptr;
		}
		//if this next node val is greater than list1 curr val, place list1 curr in front of next node
		else if (*current->next->data > *list1.head_->data)
		{
			Node* temp = current->next;
			current->next = list1.head_;
			list1.head_ = list1.head_->next;
			current = current->next;
			current->next = temp;
		}
		else
		{
			current = current->next;
		}
	}
	return true;
}

template<class ItemType>
bool List342<ItemType>::Insert(ItemType* obj)
{
	Node* new_node = new Node;
	new_node->data = obj;
	//if empty list
	if (head_ == nullptr)
	{
		head_ = new_node;
		return true;
	}
	//if duplicate item
	if (*obj == *head_->data)
	{
		return false;
	}
	if (*obj < *head_->data)
	{
		new_node->next = head_;
		head_ = new_node;
		return true;
	}
	Node* ptr_node = head_;
	while ((ptr_node->next != nullptr) && (*ptr_node->next->data < *obj))
	{
		ptr_node = ptr_node->next;
	}

	if ((ptr_node->next != nullptr) && (*ptr_node->next->data == *obj))
	{
		return false;
	}
	new_node->next = ptr_node->next;
	ptr_node->next = new_node;
	return true;
}

template <class ItemType>
bool List342<ItemType>::Remove(ItemType target, ItemType& result)
{
	Node* curr;
	if (isEmpty())
	{
		return false;
	}
	//head is target, delete head
	if (*head_->data == target)
	{
		curr = head_;
		head_ = head_->next;
		result = *curr->data;
		delete curr;
		curr = nullptr;
		return true;
	}
	Node* ptr_node = head_;
	//iterate through list
	while (ptr_node->next != nullptr && *ptr_node->next->data < target)
	{
		ptr_node = ptr_node->next;
	}
	//target not found
	if (ptr_node->next == nullptr)
	{
		return false;
	}
	//target found
	if (*ptr_node->next->data == target)
	{
		curr = ptr_node->next;
		result = *curr->data;
		ptr_node->next = ptr_node->next->next;
		delete curr;
		curr = nullptr;
		return true;
	}
	return false;
}

template<class ItemType>
bool List342<ItemType>::Peek(ItemType target, ItemType& result) const
{
	Node* curr;
	if (isEmpty())
	{
		return false;
	}
	if (*head_->data == target)
	{
		curr = head_;
		result = *curr->data;
		return true;
	}
	Node* ptr_node = head_;
	while (ptr_node->next != nullptr && *ptr_node->next->data < target)
	{
		ptr_node = ptr_node->next;
	}
	if (ptr_node->next == nullptr)
	{
		return false;
	}
	if (*ptr_node->next->data == target)
	{
		curr = ptr_node->next;
		result = *curr->data;
		return true;
	}
	return false;
}

template<class ItemType>
void List342<ItemType>::DeleteList()
{
	
	while (head_ != nullptr)
	{
		Node* temp_ptr_node = new Node;
		temp_ptr_node = head_;
		head_ = head_->next;
		delete temp_ptr_node;
		temp_ptr_node = nullptr;
	}
}

template<class ItemType>
bool List342<ItemType>::operator==(const List342& list) const
{
	Node* ptr_this = head_;
	Node* ptr_list = list.head_;
	if (this->isEmpty() && list.isEmpty())
	{
		return true;
	}
	while (ptr_this != nullptr && ptr_list != nullptr)
	{
		if (ptr_this->data != ptr_list->data)
		{
			cout << "false" << endl;
			return false;
		}
		ptr_this = ptr_this->next;
		ptr_list = ptr_list->next;
	}
	cout << "true" << endl;
	return true;
}

template<class ItemType>
bool List342<ItemType>::operator!=(const List342& list) const
{
	if (this->isEmpty() && list.isEmpty())
	{
		return false;
	}
	Node* ptr_this = head_;
	Node* ptr_list = list.head_;
	while (ptr_this != nullptr && ptr_list != nullptr)
	{
		if (ptr_this->data == ptr_list->data)
		{
			cout << "false" << endl;
			return false;
		}
		ptr_this = ptr_this->next;
		ptr_list = ptr_list->next;

	}
	cout << "true" << endl;
	return true;
}

template<class ItemType>
List342<ItemType>& List342<ItemType>::operator=(const List342& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}
	Node* ptr_node;
	Node* source;
	Node* dest;
	this->DeleteList();
	if (rhs.head_ == nullptr)
	{
		return *this;
	}
	dest = new Node;
	dest->data = rhs.head_->data;
	this->head_ = dest;
	source = rhs.head_->next;
	//iterate through rhs
	while (source != nullptr)
	{
		ptr_node = new Node;
		ptr_node->data = source->data;
		dest->next = ptr_node;
		dest = dest->next;
		source = source->next;
	}
	return *this;
}
template <class ItemType>
List342<ItemType> List342<ItemType>::operator+(const List342<ItemType>& list) const
{
	List342<ItemType> temp = *this;
	List342<ItemType> temp2 = list;
	temp.Merge(temp2);
	return temp;
}
template <class ItemType>
List342<ItemType> List342<ItemType>::operator+=(const List342<ItemType>& list1)
{
	List342<ItemType> temp = list1;
	this->Merge(temp);
	return *this;
}

#endif