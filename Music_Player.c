#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 100

#define max(a,b) (((a) > (b)) ? (a) : (b))

typedef struct song
{
  char song[SIZE];
  char singer[SIZE];
  char lyricist[SIZE];
  char album[SIZE];
  char composer[SIZE];
  char genre[SIZE];
  int duration;
}Song;

// Create Node
typedef struct Node 
{
  Song key;
  struct Node *left;
  struct Node *right;
  int height;
}Node;

// Calculate height
int height(Node *N) 
{
  if (N == NULL)
    return 0;
  return N->height;
}

// Create a node
Node *newNode() 
{
  Node *node = (Node*)malloc(sizeof(Node));
    
  printf("Enter the name of the song: ");
  getchar();
  scanf("%[^\n]", node->key.song);
  getchar();
  printf("Enter the name of the singer: ");
  scanf("%[^\n]", node->key.singer);
  getchar();
  printf("Enter the name of the lyricist: ");
  scanf("%[^\n]", node->key.lyricist);
  getchar();
  printf("Enter the name of the album/film: ");
  scanf("%[^\n]", node->key.album);
  getchar();
  printf("Enter the name of the composer: ");
  scanf("%[^\n]", node->key.composer);
  getchar();
  printf("Enter the genre: ");
  scanf("%[^\n]", node->key.genre);
  getchar();
  printf("Enter the duration (in seconds): ");
  scanf("%d", &(node->key.duration));
  getchar();

  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return node;
}

// Right rotate
Node *rightRotate(Node *y) 
{
  Node *x = y->left;
  Node *T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;

  return x;
}

// Left rotate
Node *leftRotate(Node *x) 
{
  Node *y = x->right;
  Node *T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;

  return y;
}

// Get the balance factor
int getBalance(Node *N) 
{
  if (N == NULL)
    return 0;
  return height(N->left) - height(N->right);
}

// Insert node
//----Q1
Node *insertNode(Node *node, Node* curr) 
{
  // Find the correct position to insertNode the node and insertNode it
  if (node == NULL)
    return curr;

  if (strcmp(curr->key.singer, node->key.singer) < 0)
    node->left = insertNode(node->left, curr);
  else if (strcmp(curr->key.singer, node->key.singer) > 0)
    node->right = insertNode(node->right, curr);
  else
    return node;

  // Update the balance factor of each node and
  // Balance the tree
  node->height = 1 + max(height(node->left), height(node->right));

  int balance = getBalance(node);
  if (balance > 1 && strcmp(curr->key.singer, (node->left)->key.singer) < 0)
    return rightRotate(node);

  if (balance < -1 && strcmp(curr->key.singer, (node->right)->key.singer) > 0)
    return leftRotate(node);

  if (balance > 1 && strcmp(curr->key.singer, (node->left)->key.singer) > 0) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  if (balance < -1 && strcmp(curr->key.singer, (node->right)->key.singer)) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}


Node *minValueNode(Node *node) 
{
  Node *current = node;

  while (current->left != NULL)
    current = current->left;

  return current;
}

Node *copyNode(Node *root,Node *temp)
{
  strcpy(root->key.song, temp->key.song);
  strcpy(root->key.singer, temp->key.singer);
  strcpy(root->key.lyricist, temp->key.lyricist);
  strcpy(root->key.album, temp->key.album);
  strcpy(root->key.composer, temp->key.composer);
  strcpy(root->key.genre, temp->key.genre);
  root->key.duration = temp->key.duration;
  
  return root;
}

// Delete a nodes
Node *deleteNode(Node *root, char* singer) 
{
  // Find the node and delete it
  if (root == NULL)
  {
    return root;
  }

  if (strcmp(singer, root->key.singer) < 0)
  {
    root->left = deleteNode(root->left, singer);
  }

  else if (strcmp(singer, root->key.singer) > 0)
  {
    root->right = deleteNode(root->right, singer);
  }

  else 
  {
    if ((root->left == NULL) || (root->right == NULL)) 
    {
      Node *temp = root->left ? root->left : root->right;

      if (temp == NULL)
      {
        temp = root;
        root = NULL;
      }
      else
      {
        *root = *temp;
      }
      free(temp);
    }
    else
    {
      Node *temp = minValueNode(root->right);

      root = copyNode(root,temp);

      root->right = deleteNode(root->right, temp->key.singer);
    }
  }

  if (root == NULL)
  {
    return root;
  }

  // Update the balance factor of each node and
  // balance the tree
  root->height = 1 + max(height(root->left), height(root->right));

  int balance = getBalance(root);
  if (balance > 1 && getBalance(root->left) >= 0)
  {
    return rightRotate(root);
  }

  if (balance > 1 && getBalance(root->left) < 0) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }

  if (balance < -1 && getBalance(root->right) <= 0)
    return leftRotate(root);

  if (balance < -1 && getBalance(root->right) > 0) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;
}

// Function to find minimum value node in a given BST
Node* findMinimum(Node* root){
  while (root->left)
      root = root->left;
  return root;
}

Node* Getsuccessor(Node* root, Node *node)
{
    Node* succ = NULL;
    /*Start from root and search for successor down the tree*/
    int flag=1;
    while (root != NULL && flag==1){
        // if right subtree exist
        if (strcmp(root->key.singer, node->key.singer) == 0 && root->right != NULL)
        {
            succ = findMinimum(root->right);
            flag=0;
        }
        // if node does not have a right subtree
        else if (strcmp(node->key.singer, root->key.singer) < 0){
            succ = root;
            root = root->left;
        }
        else if (strcmp(node->key.singer, root->key.singer) > 0)
        {
            root = root->right;
        }
        else
        {
            flag=0;
        }
    }
    return succ;
}

Node* findMaximum(Node* root){
  while (root->right)
      root = root->right;
  return root;
}

Node* Getpredecessor(Node* root, Node *node)
{
  Node* pre = NULL;
  /*Start from root and search for successor down the tree*/
  int flag=1;
  while (root != NULL && flag==1)
  {
      // if right subtree exist
      if (strcmp(root->key.singer, node->key.singer) == 0 && root->left != NULL)
      {
          pre = findMaximum(root->left);\
          flag=0;
      }
      // if node does not have a right subtree
      else if (strcmp(node->key.singer, root->key.singer) < 0)
      {          
        root = root->left;
      }
      else if (strcmp(node->key.singer, root->key.singer) > 0)
      {
        pre = root;
        root = root->right;
      }
      else
      {
          flag=0;
      }
  }
  return pre;
}

void inorder(Node *root,int *index)
{
  if(root != NULL)
  {
    inorder(root->left, index);
    printf("%d. %s\n", *index, root->key.song);
    (*index)++;
    inorder(root->right, index);
  }
}

void trav(Node* root, int *index)
{
  if(root != NULL)
  {
    trav(root->left, index);
    (*index)++;
    trav(root->right, index);
  }
}

Node *find(Node *root, int selectedSong, int *index)
{
  Node *ret_val=NULL;
  if(root != NULL)
  {
    Node* found = find(root->left, selectedSong, index);
    if(found != NULL)
    {
      ret_val = found;
    }
    else if(*index == selectedSong)
    {
      ret_val = root;
    }
    else
    {
      (*index)++;
      ret_val = find(root->right, selectedSong, index);
    }
  }

  return ret_val;
}

void displaySong(Node* root) 
{
    Node* current = (Node*)malloc(sizeof(Node));
    current = NULL;

    int index = 1;
    inorder(root, &index);

    int selectedSong;
    printf("\nEnter the serial number of the song to play: ");
    scanf("%d", &selectedSong);
   
    index = 1;
    current = find(root,selectedSong, &index);

    if (current != NULL)
    {
        printf("\nPlaying %s by %s from the album/film %s\n", current->key.song, current->key.singer, current->key.album);
        Node *next = Getsuccessor(root,current);
        if (next != NULL) 
        {
          printf("\nNext song is: %s\n", next->key.song);
        }

        Node *prev = Getpredecessor(root,current);
        if (prev!=NULL)
        {          
          printf("Previous song is: %s\n", prev->key.song);
        }

        printf("\nSelect an option: (1) Next song, (2) Previous song, (3) Exit\n");

        int option;
        scanf("%d", &option);
        if (option == 1 && next != NULL)
        {
             printf("\nPlaying %s by %s from the album/film %s\n", next->key.song, next->key.singer, next->key.album);
        }
        else if (option == 2 && prev !=NULL)
        {
           
             printf("\nPlaying %s by %s from the album/film %s\n", prev->key.song, prev->key.singer, prev->key.album);
        }
        else
        {
            printf("\nExiting music player...\n");
        }
    }
    else
    {
        printf("\nInvalid serial number. Please try again.\n");
        // inorder(root, 1);
    }
}

//7
void display_song_details(Node* root, int serial_number) 
{
    Node* current = (Node*)malloc(sizeof(Node));
    current = NULL;

    int index = 1;
    current = find(root, serial_number, &index);

    if(current == NULL)
    {
        printf("Song with serial number %d does not exist\n",serial_number);
    }
    else
    {
        printf("Song: %s\n",current->key.song);
        printf("Singer: %s\n", current->key.singer);
        printf("Lyricist: %s\n", current->key.lyricist);
        printf("Album/Film: %s\n", current->key.album);
        printf("Composer: %s\n", current->key.composer);
        printf("Genre: %s\n", current->key.genre);
        printf("Duration: %d\n", current->key.duration);
        int k;
        int t;
        char direction[10];
        printf("Enter direction 'up' or 'down' and position fron given song\n");
        scanf("%s%d",direction,&k);
        t = k;
        if(strcmp(direction, "down") == 0)
        {
          while(current != NULL && k > 0)
          {
            k--;
            current = Getsuccessor(root,current);
          }
          if(current == NULL)
          {
            printf("%d th song from index %d in downward direction does not exist\n", t, index);
          }
          else
          {
            printf("Song: %s\n",current->key.song);
            printf("Singer: %s\n", current->key.singer);
            printf("Lyricist: %s\n", current->key.lyricist);
            printf("Album/Film: %s\n", current->key.album);
            printf("Composer: %s\n", current->key.composer);
            printf("Genre: %s\n", current->key.genre);
            printf("Duration: %d\n", current->key.duration);
          }
        }
        else if(strcmp(direction, "up") == 0)
        {
          while(current != NULL && k > 0)
          {
            k--;
            current = Getpredecessor(root, current);
          }
          if(current == NULL)
          {
            printf("%d th song in upward direction does not exist\n",t);
          }
          else
          {
            printf("Song: %s\n",current->key.song);
            printf("Singer: %s\n", current->key.singer);
            printf("Lyricist: %s\n", current->key.lyricist);
            printf("Album/Film: %s\n", current->key.album);
            printf("Composer: %s\n", current->key.composer);
            printf("Genre: %s\n", current->key.genre);
            printf("Duration: %d\n", current->key.duration);
          }           
        }
        else
        {
            printf("Entered Direction is Invalid!!\n");
        }       
    }
}

void PrintDes(Node *root)
{
  if(root != NULL)
  {
    PrintDes(root->right);
    printf("Song: %s\n", root->key.song);
    printf("Singer: %s\n", root->key.singer);
    printf("Lyricist: %s\n", root->key.lyricist);
    printf("Album/Film: %s\n", root->key.album);
    printf("Composer: %s\n", root->key.composer);
    printf("Genre: %s\n", root->key.genre);
    printf("Duration: %d\n", root->key.duration);
    printf("--------------\n");
    PrintDes(root->left);
  }
}

// Print the tree
void PrintAsc(Node *root) 
{
  if (root != NULL) 
  {
    PrintAsc(root->left);

    printf("Song: %s\n", root->key.song);
    printf("Singer: %s\n", root->key.singer);
    printf("Lyricist: %s\n", root->key.lyricist);
    printf("Album/Film: %s\n", root->key.album);
    printf("Composer: %s\n", root->key.composer);
    printf("Genre: %s\n", root->key.genre);
    printf("Duration: %d minutes\n", root->key.duration);
    printf("\n");
    
    PrintAsc(root->right);
  }
}

//5
Node* create_song(char song[],char singer[], char lyricist[], char album[], char composer[], char genre[], int duration);
Node *createPlaylist(int argc,char argv[8][100], Node *root);
Node* helper(Node* root)
{
  int argc = 0;
  char attribute[8][100];
  char argv[8][100];
  printf("Enter the number of attributes you want to select for playlist\n");
  scanf("%d", &argc);
  getchar();
  for(int i = 0; i < argc; i++)
  {
      char temp[100];
      char att[100];
      printf("Enter attribute you choose: ");
      scanf("%[^\n]", att);
      getchar();
      strcpy(attribute[i], att);
      printf("Enter the value of this attribute: ");
      scanf("%[^\n]", temp);
      strcpy(argv[i], temp);
      getchar();
  }
  Node *temp=createPlaylist(argc,argv, root);
  return temp;
}

//8
int str_to_int(char str[]);
Node* create_song(char song[],char singer[], char lyricist[], char album[], char composer[], char genre[], int duration)
{
  Node* new_song = (Node*) malloc(sizeof(Node));
  strcpy(new_song->key.song, song);
  strcpy(new_song->key.singer, singer);
  strcpy(new_song->key.lyricist, lyricist);
  strcpy(new_song->key.album, album);
  strcpy(new_song->key.composer, composer);
  strcpy(new_song->key.genre, genre);
  new_song->key.duration = duration;

  new_song->left= NULL;
  new_song->right=NULL;
  new_song->height=1;

  return new_song;
}

void traverse(Node **root, Node *curr, int argc, char argv[8][100])
{
    if(curr !=  NULL)
    {
        int flag = 1;
        for(int i = 0; i < argc && flag == 1; i++)
        {
          if (strcmp(curr->key.song,argv[i])==0 ||
              strcmp(curr->key.singer, argv[i])== 0 ||
              strcmp(curr->key.lyricist, argv[i]) == 0 ||
              strcmp(curr->key.album, argv[i]) == 0 ||
              strcmp(curr->key.composer,argv[i]) == 0 ||
              strcmp(curr->key.genre,argv[i]) == 0 ||
              curr->key.duration == str_to_int(argv[i]))
          {
              flag = 1;
          }
          else
          {
              flag=0;
          }
        }
        if(flag == 1)
        {
            Node* new_song = create_song(curr->key.song,curr->key.singer, curr->key.lyricist, curr->key.album, curr->key.composer, curr->key.genre, curr->key.duration);
            *root = insertNode(*root, new_song);
        }
        traverse(root,curr->left,argc,argv);
        traverse(root,curr->right,argc,argv);
    }
}

Node *createPlaylist(int argc,char argv[8][100], Node *root)
{
  Node *root1 = (Node *)malloc(sizeof(Node));
  root1 = NULL;
  
  traverse(&root1, root, argc, argv);
  
  return root1;
}

Node *display_song(Node *root, int serial_number) {
    Node* current_song;
    int index = 1;

    current_song = find(root,serial_number,&index);
    if (current_song != NULL)
    {
        printf("Song: %s\n", current_song->key.song);
        printf("Singer: %s\n", current_song->key.singer);
        printf("Lyricist: %s\n", current_song->key.lyricist);
        printf("Album/Film: %s\n", current_song->key.album);
        printf("Composer: %s\n", current_song->key.composer);
        printf("Genre: %s\n", current_song->key.genre);
        printf("Duration: %d seconds\n", current_song->key.duration);
        printf("------------------------\n\n");
    }
    else
    {
        printf("Invalid serial number.\n");
    }
    int argc = 0;
    char argv[8][100];
    printf("Enter the number of attributes you want to select for playlist\n");
    scanf("%d", &argc);
    getchar();
    for(int i = 0; i < argc; i++)
    {
        char temp[50];
        scanf("%[^\n]", temp);
        strcpy(argv[i], temp);
        getchar();
    }
    Node *temp = createPlaylist(argc,argv,root);
    return temp;
}

//9
int str_to_int(char str[])
{
    int num = 0;
    int i = 0;
    while(str[i] != '\0')
    {
        num=num*10+(str[i]-'0');
        i++;
    }
    return num;
}

void filter_by_attribute(Node *root, char att[])
{
  Node* curr = root;
  if(root != NULL)
  {
    filter_by_attribute(root->left,att);

    if( strcmp(curr->key.song,att)==0 ||
        strcmp(curr->key.singer,att) == 0 ||
        strcmp(curr->key.lyricist, att) == 0 ||
        strcmp(curr->key.album, att) == 0 ||
        strcmp(curr->key.composer, att) == 0 ||
        strcmp(curr->key.genre,att) == 0 ||
        curr->key.duration == str_to_int(att))
    {
      printf("Song: %s\n",curr->key.song);
      printf("Singer: %s\n", curr->key.singer);
      printf("Lyricist: %s\n", curr->key.lyricist);
      printf("Album/Film: %s\n", curr->key.album);
      printf("Composer: %s\n", curr->key.composer);
      printf("Genre: %s\n", curr->key.genre);
      printf("Duration: %d\n", curr->key.duration);
      printf("------------------------\n\n");
    }
    
    filter_by_attribute(root->right,att);
  }   
}

//10
int sizeTree(Node *root)
{
    if(root != NULL)
    {
      return 1 + sizeTree(root -> left) + sizeTree(root -> right);
    }
    else
    {
      return 0;
    }
}

void Search(Node *root,int target,int *index)
{
    if(root!=NULL)
    {
        Search(root->left,target,index);
        if(target==*index)
        {
            printf("Song: %s\n",root->key.song);
            printf("Singer: %s\n", root->key.singer);
            printf("Lyricist: %s\n", root->key.lyricist);
            printf("Album/Film: %s\n", root->key.album);
            printf("Composer: %s\n", root->key.composer);
            printf("Genre: %s\n", root->key.genre);
            printf("Duration: %d\n", root->key.duration);
            printf("--------------\n");
            return;
        }
        (*index)++;
        Search(root->right,target,index);
    }
}

void shuffle(Node* root)
{
    Node *temp = helper(root);
    int size = sizeTree(temp);

    int flag[100] = {0};
    time_t t;
    int idx = size;
    while(idx > 0)
    {
        srand((unsigned) time(&t)); /* Intializes random number generator */
        int random_index = rand() % size;//generates random numbers from 0 to size-1
        if(flag[random_index] == 0)
        {
            int index=1;
            Search(temp, random_index, &index);
           
            flag[random_index] = 1;
            idx--;
        }        
    }
    printf("Printed all songs of Playlist randomly!!\n");
}

//11
void Print(Node *root, char singer1[], char singer2[])
{
   if (root == NULL)
   {
    return;
   }
 
   /* Since the desired o/p is sorted, recurse for left subtree first
      If root->data is greater than k1, then only we can get o/p keys
      in left subtree */
     
   if (strcmp(root->key.singer, singer1) > 0 && strcmp(root->key.singer, singer2) > 0)
   {
     Print(root->left, singer1, singer2);
   }
   else if(strcmp(root->key.singer, singer1) < 0 && strcmp(root->key.singer, singer2) < 0)
   {
    Print(root->right, singer1, singer2);
   }
   else
   {
    Print(root -> left, singer1, singer2);

    printf("Song: %s\n",root->key.song);
    printf("Singer: %s\n", root->key.singer);
    printf("Lyricist: %s\n", root->key.lyricist);
    printf("Album/Film: %s\n", root->key.album);
    printf("Composer: %s\n", root->key.composer);
    printf("Genre: %s\n", root->key.genre);
    printf("Duration: %d\n", root->key.duration);
    printf("--------------\n");
    
    Print(root -> right, singer1, singer2);
   }
}

Node* finder(Node* root, char str[])
{
  if(root == NULL)
  {
  return NULL;
  }

  Node* temp = finder(root -> left, str);
  if(temp != NULL)
  {
  return temp;
  }
  if(strcmp(root -> key.song, str) == 0)
  {
  return root;
  }
  return finder(root->right, str);
}

int main() 
{
  Node *root = (Node*)malloc(sizeof(Node));
  root = NULL;

  FILE* fp;
  char line[200];
  fp = fopen("list.txt", "r");
  if (fp == NULL)  
  {
    printf("Error opening file.");
    exit(1);
  }

  while(fgets(line, sizeof(line), fp) != NULL)
  {
    Node *node = (Node*)malloc(sizeof(Node));
    sscanf(line, "%[^;]; %[^;]; %[^;]; %[^;]; %[^;]; %[^;]; %d", node->key.song, node->key.singer, node->key.lyricist, node->key.album, node->key.composer, node->key.genre, &(node->key.duration));

    node->left = NULL;
    node->right = NULL;
    node->height = 1;

    root = insertNode(root, node);
  }

  fclose(fp);

  printf("Hello :) !!!....\n");
  printf("Welcome to our Music Player\n");
  int flag=1;
  while(flag == 1)
  {
      printf("1.Write a function, InsertSong(), which reads a song from user and insert into a tree database of structures.\n");
      printf("2.Remove duplicate entries from Records\n");
      printf("3.Play playlist in ascending as well as in descending order\n");
      printf("4.Delete all songs from playlist with given song name and singer\n");
      printf("5.Create a play-list based on the attribute and its value\n");
      printf("6.Play a song in playlist as per serial number and play next or previous song\n");
      printf("7.Play a song in playlist as per serial number and play kth next or kth previous song\n");
      printf("8.Play a given song from Playlist and create a new Playlist selecting one or more attributes from this song\n");
      printf("9.Play only songs in Playlist matching given attribute value\n");
      printf("10.Randomly play songs from Database matching given attributes value\n");
      printf("11.Search songs belonging to singers whose names are in-between singer-name-1 and singer-name-2, in lexicographic sorting sense.\n");
      printf("------------------------\n");
      int t;
      printf("Enter any negative number to exit our music player\n");
      scanf("%d",&t);
      Node *temp;
      if(t>=0)
      {
          switch(t)
          {
              case 1:; Node* dss = newNode();
                      root = insertNode(root, dss);
                      PrintAsc(root);
                      break;
              case 2: PrintAsc(root);
                      break;
              case 3: printf("Printing ascending Order\n\n\n");
                      PrintAsc(root);
                      printf("Printing descending Order\n\n\n");
                      PrintDes(root);
                      break;
              case 4:; char str1[100]; char str2[100];
                      printf("Enter singer name to delete\n");
                      getchar();
                      scanf("%[^\n]", str1);
                      getchar();
                      temp = deleteNode(root, str1);
                      PrintAsc(temp);
                      printf("Enter Song's name to delete Song\n");
                      scanf("%[^\n]", str2);
                      getchar();
                      Node* sec = finder(root, str2);
                      temp = deleteNode(root, sec->key.singer);
                      printf("Displaying modified Playlist\n");
                      PrintAsc(temp);
                      break;
              case 5: temp = helper(root);
                      printf("Displaying new Playlist\n\n");
                      PrintAsc(temp);
                      break;
              case 6: displaySong(root);
                      break;
              case 7:; int k;
                      printf("Enter serial number of song to play\n");
                      scanf("%d",&k);
                      display_song_details(root,k);
                      break;
              case 8:; int l;
                      printf("Enter serial number of song to play\n");
                      scanf("%d",&l);
                      temp = display_song(root,l);
                      printf("Displaying new Playlist as per given attributes\n");
                      PrintAsc(temp);
                      break;
              case 9:; char str3[50];
                      printf("Enter the attribute's value : ");
                      getchar();
                      scanf("%[^\n]", str3);
                      getchar();
                      filter_by_attribute(root,str3);
                      break;
              case 10: shuffle(root);
                      break;
              case 11:; char str4[100];
                      char str5[100];
                      printf("Enter first singer : ");
                      getchar();
                      scanf("%[^\n]", str4);
                      getchar();
                      printf("Enter second singer : ");
                      scanf("%[^\n]", str5);
                      getchar();
                      printf("\n");
                      Print(root, str4, str5);
                      break;
              default:printf("Invalid number entered\n");
                      break;
          }
      }
      else
      {
          flag=0;
      }
  }
  printf("Thanks for visiting our Music Player\n");
  printf("------------------------\n\n");
  printf("------------------------\n\n");

  return 0;
}