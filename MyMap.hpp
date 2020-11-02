//Function to set MST username to my_id
void get_identity(std::string &my_id)
{
  my_id = "hdpg4c";
}

//Function to empty the tree
template <typename K, typename V>
MyMap<K,V>::MyMap()
{
  root = nullptr;
}

//Function to create a new BST and return the root
template <typename K, typename V>
MyMap<K,V>::MyMap(const MyMap<K, V> &source)
{
  root = clone(source.root);
}

//Destructor function
template <typename K, typename V>
MyMap<K,V>::~MyMap()
{
  clear();
}

//Function clears and creates a new Bst and return the root
template <typename K, typename V>
MyMap<K, V> & MyMap<K,V>::operator=(const MyMap<K, V> &source)
{
  clear(); //calls the clear function
  root = clone(source.root); //create a clone bst

  return *this;
}

//Funciton which calls helper funciton and throws out of range message
template <typename K, typename V>
V & MyMap<K, V>::at(const K &key)
{
  return at_helper(root, key);
}

template <typename K, typename V>
V & MyMap<K, V>::operator[](const K &key)
{
  if(count(key) == 0) //node doesn't exist
  {
    insert(MyPair<K,V>(key)); //inserts
    return at_helper(root, key);
  }
  else
  {
    return at_helper(root, key);
  }
}

//Function to empty the list
template <typename K, typename V>
bool MyMap<K, V>::empty() const
{
  return !root; // root pointer to null/zero
}

//returns the size_helper
template <typename K, typename V>
int MyMap <K, V>::size() const
{
  return size_helper(root);
}

//Function to clear and if no nodes, then does nothing
template <typename K, typename V>
void MyMap<K, V>::clear()
{
  if(root != nullptr) //
  {
    clear_helper(root);
    root = nullptr;
  }

  return;
}

template <typename K, typename V>
void MyMap<K, V>::insert(const MyPair<K, V> &init_pair)
{
  insert_helper(root, init_pair); //calls insert_helper function
}

//Function which returns nothing if there are nodes, otherwise call the
//erase function to erase
template <typename K, typename V>
void MyMap<K, V>::erase(const K &key)
{
  if (size() == 0)
    return;
  else //if nodes possible, then erase
    erase_helper(root, key);
}

template <typename K, typename V>
MyPair<K, V> * MyMap<K,V>::find(const K & key)const
{
  return find_helper(root, key);
}

template <typename K, typename V>
void MyMap<K,V>::print()const
{
  print_helper(root, " "); //to print the output
}

template <typename K, typename V>
int MyMap<K, V>::count(const K &key)const
{
  return count_helper(root,key);
}

template <typename K, typename V>
V & MyMap<K,V>::at_helper(TreeNode<MyPair<K, V>> *&rt, const K &key)
{
  if(rt == nullptr)
    throw std::out_of_range("MyMap::at \n"); //node not found, and throws error

  if (rt->data.first == key) //key found, then
    return rt->data.second; //return value

  if (key < rt->data.first) //key is less than current key
    return at_helper(rt->left, key); //traverse left

  else  // traverse right
    return at_helper(rt->right, key);
}

//Function to start node count at zero and if there is node, then
//recursively go down left and right
template <typename K, typename V>
int MyMap<K, V>::size_helper(TreeNode<MyPair<K, V>> *rt) const
{
  if(rt == nullptr)
    return 0;
  else
    return size_helper(rt->left) + size_helper(rt->right) + 1 ;
}

//Function to help clear
template <typename K, typename V>
void MyMap<K, V>::clear_helper(TreeNode<MyPair<K, V>> *&rt)
{
  TreeNode<MyPair<K, V>>* array = rt;

  if(array != nullptr)
  {
    clear_helper(array->left); //travere down left

    clear_helper(array->right); //traverse down right

    delete array; //free the memory

    array = nullptr; //sets array to null
  }

  return;
}

//Funciton to help insert in the tree
template <typename K, typename V>
void MyMap<K,V>::insert_helper(TreeNode<MyPair<K, V>> *&rt, const MyPair<K, V> &init_pair)
{
  if(rt == nullptr) //find spot to insert node
    rt = new TreeNode<MyPair<K,V>>(init_pair, nullptr, nullptr);

  //go left if pair to insert is less than key
  else if(init_pair.first < rt->data.first)
    insert_helper(rt->left, init_pair);

  //go right if pair to insert is  greater than key
  else if(init_pair.first > rt->data.first)
    insert_helper(rt->right, init_pair);

  return;
}

template <typename K, typename V>
TreeNode<MyPair<K, V>>* MyMap<K, V>::get_min(TreeNode<MyPair<K, V>> * rt)
{
  while(rt->left != nullptr) //while value is found then
    rt = rt->left; //transver to left end

  return rt;
}

template <typename K, typename V>
void MyMap<K, V>::erase_helper(TreeNode<MyPair<K, V>> *&rt, const K &key)
{
  if(rt == nullptr) //key not found
    return;

  else if (key < rt->data.first) //traverse left
    erase_helper(rt->left, key);

  else if (key > rt->data.first) //traverse right
    erase_helper(rt->right, key);

  else
  {
    TreeNode<MyPair<K, V>>* array = rt;

    if(rt->left == nullptr) //right child exists in the subtree
      rt = rt->right;

    else if(rt ->right == nullptr) //left child exists in the subtree
      rt = rt->left;

    else
    {
      //make a pointer to minimum node
      TreeNode<MyPair<K, V>>* min_value = get_min(rt->right);

      if (min_value->right == nullptr)//min val has no right
      {
        //set rt to pointer as min above, so parent now points to min
        rt = new TreeNode<MyPair<K, V>>(min_value->data, array->left, array->right); 

        //if min_value in right was the direct of rt, set new right to
        // nullptr
        if (array->right == rt)
          rt->right = nullptr;

        erase_helper(rt->right, min_value->data.first); //calls the erase function
      }
      else //min val has a right subtree
      {
        rt = new TreeNode<MyPair<K, V>>(min_value->data, array->left, array->right);
        erase_helper(rt->right, min_value->data.first); //delete the min value
      }
    }
    delete array;
  }
}

//Function to help find key in BST
template <typename K, typename V>
MyPair<K, V> * MyMap<K,V>::find_helper(TreeNode<MyPair<K, V>> *rt, const K &key) const
{
  if(rt == nullptr) //key not found
    return nullptr;

  else if(key == rt->data.first)
    return &(rt->data);

  if(key < rt->data.first)
    return find_helper(rt->left, key);//tranverse left, if key less than current

  return find_helper(rt->right, key);//tranverse right, if key greater than
}

//Funciton to print the output
template <typename K, typename V>
void MyMap<K,V>::print_helper(TreeNode<MyPair<K, V>> *rt, std::string indent) const
{
  if(rt == nullptr) //prints right to left and top to bottom
  {
    cout << indent <<"  [empty]" << endl;
    return;
  }

  print_helper(rt->right, indent += " "); //add indentation

  cout << indent << "["<< rt->data.first << "]=" << rt->data.second << endl;

  print_helper(rt->left, indent += " "); //adds indentation

  return;
}

//Funciton that helps to count the nodes
template <typename K, typename V>
int MyMap<K,V>::count_helper(TreeNode<MyPair<K, V>> *rt, const K &key)const
{
  if(find_helper(rt, key) == nullptr) //if no node, then return zero
    return 0;

  else //else return 1
    return 1;
}

template <typename K,  typename V>
TreeNode<MyPair<K, V>> * MyMap<K,V>::clone(const TreeNode<MyPair<K, V>> *  rt)
{
  if(rt == nullptr) //returns null when left and right are not in tree
    return nullptr;

  //makes new tree
  TreeNode<MyPair<K,V>> *temp = new TreeNode<MyPair<K,V>>(rt->data,nullptr,nullptr);

  temp->left = clone(rt->left); //returns root of new tree
  temp->right = clone(rt->right);

  return temp; //returns temp
}

//Function to that accepts an arbitrary number of characters from standard input
// and builds a MyMap containing the number of occurrences for each character
//in the input
void get_letter_frequency(MyMap<char, int> &in_tree)
{
  std::string input;
  char tempChar;

  while(cin >> input) //while reading from the input file
  {
    input.append(" ");
    for(short i = 0; i < input.size(); i++) //iterates till the end of input
    {
      tempChar = input[i]; //sets the temp Char to the char i

      if(!in_tree.find(tempChar)) //if char not found then
        in_tree.insert(MyPair<char, int>(tempChar, 1)); //inserts

      else //is found then increments the char to next one
        in_tree[tempChar]++;
    }
  }
}
