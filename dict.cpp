// #include "dict.h"
// #include<sstream>
// Dict::Dict()
// {
//   root = nullptr;
//   //count=0;
// }
// Dict::~Dict()
// {
//   //delete root;
// }
// bool Dict::is_punct(char d){
 
//   char arr[14]={'.', ',', '-', ':', '!', '"', '\'', '(', ')', '?',  '[', ']', ';', '@'};
//   for(int i=0;i<14;i++){
//     if(d==arr[i]){
//       return true;
//     }
//   }
//   return false;
// }

// void Dict::insert(string k)
// {
//    root=insert1(root,k);
// }
// void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence)
// {
    
    
// //vector<string>words_of_sentence;

// string s=sentence;
// string word;
// for(char c:sentence){
// if(c==' ' || is_punct(c)){
//  if(!word.empty()){
//       for(char& ch:word){
//         if(ch>='A'&& ch<='Z'){
//             ch+='a'-'A';
//         }
//       }
//       //words_of_sentence.push_back(word);
//       insert(word);
//       word="";

//  }
// }
//  else{
//     word+=c;
//  }
// }
// if(!word.empty()){
//    for(char& ch:word){
//         if(ch>='A'&& ch<='Z'){
//             ch+='a'-'A';
//         }
//       }
//       //words_of_sentence.push_back(word);
//      insert(word);
// }

// }

// int Dict::get_word_count(string word)
// {
//   Node* n=search(word);
//   if(n!=nullptr){
//     return n->count;
//   }
//   else{
//     return 0;
//   }
// }
// void Dict::dump_dictionary1(Node* root,ofstream& mask){
// if(root==nullptr){
//   return;
// }

// dump_dictionary1(root->left,mask);
// mask<<root->key<<", "<<root->count<<endl;
// dump_dictionary1(root->right,mask);
// }


// void Dict::dump_dictionary(string filename)
// {
//      ofstream mask(filename, std::ios::out); 
//    dump_dictionary1(root,mask);
   
//      mask.close();
// }
// int main() {
//     std::ifstream inputFile("mahatma-gandhi-collected-works-volume-1.txt");

//     if (!inputFile.is_open()) {
//         std::cerr << "Error: Unable to open the input file." << std::endl;
//         return 1;
//     }

//     std::string tuple;
//     std::string sentence;

//     Dict d;

//     while (std::getline(inputFile, tuple, ')') && std::getline(inputFile, sentence)) {
//         // Get a line in the sentence
//         tuple += ')';

//         std::vector<int> metadata;    
//         std::istringstream iss(tuple);

//         // Temporary variables for parsing
//         std::string token;
//         std::cout<<"Tuple:"<<tuple<<std::endl;
//         std::cout<<"sentence"<<sentence<<std::endl;
//         // Ignore the first character (the opening parenthesis)
//         iss.ignore(1);

//         // Parse and convert the elements to integers
//         while (std::getline(iss, token, ',')) {
//             // Trim leading and trailing white spaces
//             size_t start = token.find_first_not_of(" ");
//             size_t end = token.find_last_not_of(" ");
//             if (start != std::string::npos && end != std::string::npos) {
//                 token = token.substr(start, end - start + 1);
//             }
            
//             // Check if the element is a number or a string
//             if (token[0] == '\'') {
//                 // Remove the single quotes and convert to integer
//                 int num = std::stoi(token.substr(1, token.length() - 2));
//                 metadata.push_back(num);
//             } else {
//                 // Convert the element to integer
//                 int num = std::stoi(token);
//                 metadata.push_back(num);
//             }
//                 std::cout << "Metadata: ";
//         for (int num : metadata) {
//             std::cout << num << " ";
//         }
//         std::cout << std::endl;
//         std::cout << "Sentence: " << sentence << std::endl;
//         }

//         // Now we have the string in sentence
//         // And the other info in metadata
//         // Add to the dictionary

//         // Insert in the dictionary
//         d.insert_sentence(metadata[0], metadata[1], metadata[2], metadata[3], sentence);
//     }

//     inputFile.close();

//     // Get the counts of some words
//     std::ifstream dict("counts.txt"); 
//     if (!dict.is_open()) {
//         std::cerr << "Error: Unable to open the file." << std::endl;
//         return 1;
//     }

//     bool passed = true;
//     std::string l;
//     while (std::getline(dict, l)) {
//         std::istringstream iss(l);
//         std::string key;
//         int value;

//         if (std::getline(iss, key, ',') && iss >> value) {
//             if(d.get_word_count(key) != value) {
//                 cout << "Expected count for word " << key << ": " << value << ", received: " << d.get_word_count(key) << endl;
//                 passed = false; 
//                 break;
//             }
//         }
//     }

//     if (passed) {
//         cout << "Passed" << endl;
//     } else {
//         cout << "Failed" << endl;
//     }

//     dict.close();

//     return 0;
// }








/* ------------------------------------------------------------------------------------------- */
#include "dict.h"

Dict::Dict()
{
    //int count;
   // vector<WordCount> v;
   v.resize(100000);
    for(int i=0;i<v.size();i++){
        v[i].word="-1";
        v[i].count=-1;
    }
    bank_code = 0;
    page = 0;
    paragraph = 0;
    sentence_no = 0;

    // Implement your function here
}

int Dict::hash_final(string d)
{

    int hash=0;
    for(int i=0; i<d.length(); i++){
      hash=(hash*31+d[i])%v.size();
    }
    return hash;
}
bool Dict::is_punct(char d){
  //. , - : ! " ' ( ) ? — [ ] “ ” ‘ ’ ˙ ; @
  char arr[14]={'.', ',', '-', ':', '!', '"', '\'', '(', ')', '?',  '[', ']', ';', '@'};
  for(int i=0;i<14;i++){
    if(d==arr[i]){
      return true;
    }
  }
  return false;
}
void Dict::insert1(string d)
{
 // cout<<d<<endl;
 int x=hash_final(d);
 long long initial_position=x;
 long long j=1;
 while (v[x].word != "-1") {
        x = (initial_position + j) % v.size();
        j++;
        if (x == initial_position) {
            return; // Avoid infinite loops
        }
    }
    // WordCount av;
    // av.word = d;
    // av.count = 1;
    // v[x] = av;
    v[x].word = d;
    v[x].count=1;
 }

bool Dict::does_exist(string d)
{
 int x=hash_final(d); 
 //cout<<d<<endl;
 //cout<<x<<endl;
// int y=hash2(d);
 long long initial_position=x;
 long long j = 1;
   //cout<<d<<endl;
  if (v[x].word == d) {
    //cout<<"hi"<<endl;
            return true;
        }
    while (v[x].word != "-1") {
        
        x = (initial_position + j) % v.size();
        j++;
         if (v[x].word == d) {
            return true;
        }
        if (x == initial_position) {
            break; // Avoid infinite loops
        }
    }
    return false;
}

int Dict:: search(string d){
 int x=hash_final(d);
 long long initial_position=x;
 long long j=1;
  if (v[x].word == d) {
            return x;
        }
 while (v[x].word != "-1") {
      
        x = (initial_position + j) % v.size();
        j++;
        if (v[x].word == d) {
            return x;
        }
        if (x == initial_position) {
           break; // Avoid infinite loops
        }
    }
    return x;
}

Dict::~Dict()
{
    // Implement your function here

}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
    // Implement your function here 
  string s=sentence;
  string word;
  //cout<<word<<endl;
  for(char c:s){
   // cout<<c<<endl;
  if(c==' ' || is_punct(c)){
    //cout<<"hi"<<endl;
  if(!word.empty()){
      for(char& ch:word){
       // cout<<"hi"<<endl;
        if(ch>='A'&& ch<='Z'){
            ch+='a'-'A';
        }
      }
      //cout<<word;
      //words_of_sentence.push_back(word);

      if(!does_exist(word)){
        //cout<<"hi"<<endl; 
        insert1(word);
        word="";
      }
      else{
       //cout<<"hi"<<endl; 
       //cout<<word<<endl;
        int m=search(word);
        //if (m != -1) {
          v[m].count=v[m].count+1;
        //}
         word = "";
      }
     //word = "";
}
  }
 else{
  //cout<<"hi"<<endl;
 // cout<<c<<endl;
    word+=c;
    // cout<<word<<endl;
 }

  }
if(!word.empty()){
   for(char& ch:word){
        if(ch>='A'&& ch<='Z'){
            ch+='a'-'A';
        }
      }
      //words_of_sentence.push_back(word);
      if(!does_exist(word)){
        insert1(word);
      }
      else{
        int m=search(word);
        //if (m != -1) {
          v[m].count++;
     // }
    }

    }
  
}

int Dict::get_word_count(string word)
{
    int count=0;
    for (auto &wc : v) {
        if (wc.word == word) {
            count= wc.count;
            break;
        }
    }
    return count;
    return -1;
}



void Dict::dump_dictionary(string filename)
{
    // Implement your function here
   ofstream mask(filename,std::ios::out); 
   int j=0;
   while (j<v.size()){
        if(v[j].word!="-1"){
        mask<<v[j].word<<", "<<v[j].count<<endl;
        }

        j++;
    }
     mask.close();

}
// int main() {
//     // Test the Dict class
//     Dict dict;
//     dict.insert_sentence(1, 1, 1, 1, "This is a test sentence.");
//     dict.insert_sentence(1, 1, 1, 2, "is test sentence.");
//     std::cout << "Word count for 'test': " << dict.get_word_count("test") << std::endl;
//      std::cout << "Word count for 'sentence': " << dict.get_word_count("sentence") << std::endl;
//         dict.dump_dictionary("output_dict.txt");
//      return 0;
// }
// int main() {
//     std::ifstream inputFile("mahatma-gandhi-collected-works-volume-1.txt");

//     if (!inputFile.is_open()) {
//         std::cerr << "Error: Unable to open the input file." << std::endl;
//         return 1;
//     }

//     std::string tuple;
//     std::string sentence;

//     Dict d;

//     while (std::getline(inputFile, tuple, ')') && std::getline(inputFile, sentence)) {
//         // Get a line in the sentence
//         tuple += ')';

//         std::vector<int> metadata;    
//         std::istringstream iss(tuple);

//         // Temporary variables for parsing
//         std::string token;
//         std::cout<<"Tuple:"<<tuple<<std::endl;
//         std::cout<<"sentence"<<sentence<<std::endl;
//         // Ignore the first character (the opening parenthesis)
//         iss.ignore(1);

//         // Parse and convert the elements to integers
//         while (std::getline(iss, token, ',')) {
//             // Trim leading and trailing white spaces
//             size_t start = token.find_first_not_of(" ");
//             size_t end = token.find_last_not_of(" ");
//             if (start != std::string::npos && end != std::string::npos) {
//                 token = token.substr(start, end - start + 1);
//             }
            
//             // Check if the element is a number or a string
//             if (token[0] == '\'') {
//                 // Remove the single quotes and convert to integer
//                 int num = std::stoi(token.substr(1, token.length() - 2));
//                 metadata.push_back(num);
//             } else {
//                 // Convert the element to integer
//                 int num = std::stoi(token);
//                 metadata.push_back(num);
//             }
//                 std::cout << "Metadata: ";
//         for (int num : metadata) {
//             std::cout << num << " ";
//         }
//         std::cout << std::endl;
//         std::cout << "Sentence: " << sentence << std::endl;
//         }

//         // Now we have the string in sentence
//         // And the other info in metadata
//         // Add to the dictionary

//         // Insert in the dictionary
//         d.insert_sentence(metadata[0], metadata[1], metadata[2], metadata[3], sentence);
//     }

//     inputFile.close();

//     // Get the counts of some words
//     std::ifstream dict("counts.txt"); 
//     if (!dict.is_open()) {
//         std::cerr << "Error: Unable to open the file." << std::endl;
//         return 1;
//     }

//     bool passed = true;
//     std::string l;
//     while (std::getline(dict, l)) {
//         std::istringstream iss(l);
//         std::string key;
//         int value;

//         if (std::getline(iss, key, ',') && iss >> value) {
//             if(d.get_word_count(key) != value) {
//                 cout << "Expected count for word " << key << ": " << value << ", received: " << d.get_word_count(key) << endl;
//                 passed = false; 
//                 break;
//             }
//         }
//     }

//     if (passed) {
//         cout << "Passed" << endl;
//     } else {
//         cout << "Failed" << endl;
//     }

//     dict.close();

//     return 0;
// }
