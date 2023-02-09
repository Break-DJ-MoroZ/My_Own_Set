#include <iostream>

template <class Type>
class Set
{
public:
	Set():
		head_(nullptr)
	{}

	/*Set(const Set& T)
	{
		
	}*/

	Set(Set&& T) noexcept
	{
		head_ = T.head_;
		T.head_ = nullptr;
	}

	const Set& operator= (Set&& T) noexcept
	{
		Node* temp = T.head_;
		T.head_ = head_;
		head_ = temp;

		return this;
	}

	~Set()
	{
		while (head_)
		{
			Node* temp = head_;
			head_ = head_->next_;
			delete temp;
		}
	}

	void insert(const Type& key)
	{
		Node* temp = head_;

		bool isUnique = true;

		if (!temp)
		{
			head_ = new Node(key);
		}
		else if (key < temp->key_)
		{
			head_ = new Node(key, temp);
		}
		else if (temp->key_ != key)
		{
			while (isUnique)
			{
				if (!(temp->next_))
				{
					temp->next_ = new Node(key);
					isUnique = false;
				}
				else if (key == (temp->next_)->key_)
				{
					isUnique = false;
				}
				else if (key < (temp->next_)->key_)
				{
					temp->next_ = new Node(key, temp->next_);
					isUnique = false;
				}
				else
				{
					temp = temp->next_;
				}
			}
		}
	}

	bool search(const Type& key) const
	{
		bool isInSet = false;
		Node* temp = head_;

		if (temp && key < temp->key_)
		{
			temp = nullptr;
		}

		while (temp && !isInSet)
		{
			(key == temp->key_)? isInSet = true : temp = temp->next_;
		}

		return isInSet;
	}

	void deleteKey(const Type& key)
	{
		bool isInSet = true;

		Node* temp = head_;

		if (temp && (key == temp->key_))
		{
			head_ = temp->next_;
			delete temp;
			isInSet = false;
		}
		else if (temp && (key < temp->key_))
		{
			std::cout << "There is no this key in the set!\n";
			isInSet = false;
		}
		else if (!temp)
		{
			std::cout << "There are not items in the set!\n";
		}
		else
		{
			while (isInSet)
			{
				if (!(temp->next_))
				{
					std::cout << "There is no this key in the set!\n";
					isInSet = false;
				}
				else if (key == (temp->next_)->key_)
				{
					Node* deletThisItem = temp->next_;
					temp->next_ = (temp->next_)->next_;
					delete deletThisItem;

					isInSet = false;
				}
				else
				{
					temp = temp->next_;
				}
			}
		}
	}

private:

	struct Node
	{
		Node(const Type& data, Node* next = nullptr) :
			key_(data),
			next_(next)
		{}
		Type key_;
		Node* next_;
	};

	Node* head_;
};



int main()
{
	Set<int> a;

	bool b = a.search(-12);
	a.insert(0);
	a.insert(-10);
	a.insert(1);
	a.insert(-7);
	a.insert(-8);
	a.insert(13);
	a.insert(13);
	a.insert(14);
	a.insert(-10);
	a.insert(-8);
	a.insert(28);
	a.insert(12);
	a.insert(0);
	a.insert(12);

	b = a.search(-10);
	b = a.search(0);
	b = a.search(-11);
	b = a.search(0);
	b = a.search(12);
	b = a.search(-98);
	b = a.search(128);
	b = a.search(28);
	b = a.search(-17);

	a.deleteKey(-8);
	a.deleteKey(-12);
	a.deleteKey(29);
	a.deleteKey(-10);
	a.deleteKey(28);
	a.deleteKey(-8);
	a.deleteKey(0);


	return 0;
}