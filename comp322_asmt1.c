#include <stdio.h>
#include <stdlib.h>

/* Define structures and global variables, including
linked list type and PCB type */

int max_processes = 0;

struct genericNameOne
{
   int process;
   struct genericNameOne *link;
};
typedef struct genericNameOne linked_list_type;
struct genericNameTwo
{
   int parent;
   linked_list_type *children;
} *pcb = NULL;
typedef struct genericNameTwo pcb_type;
/***************************************************************/
void optionOne() 
{
	/* declare local vars */
   int i;
	/* prompt for maximum number of processes */
   printf("\nEnter maximum number of processes: ");
   scanf("%d", &max_processes);
   printf("%d\n", max_processes);
	/* allocate memory for dynamic array of PCBs */
   pcb = malloc(max_processes * sizeof(pcb_type));
	/* Define PCB[0] */
   pcb[0].parent = 0;
   pcb[0].children = NULL;
	/* Intitialize all other indices' parent to -1 */
   for(i = 1; i < max_processes; i++)
   {
      pcb[i].parent = -1;
   }
	return;
}
	
/***************************************************************/
void optionTwo() 
{
	/* define local vars */
   int p;
   int q = 1;
   int num_children = 0;
   linked_list_type *new_child;
   linked_list_type *next_child;
	/* prompt for parent process index */
   printf("\nEnter the parent process index: ");
   scanf("%d", &p);
   printf("%d\n", p);
	/* search for next unused process q (parent=-1), using while loop */ 
   while(pcb[q].parent != -1)
   {
      q++;
   }
	/* allocate memory for new child PCB[q], set process index and initilize link to NULL */ 
   new_child = (linked_list_type *)malloc(sizeof(linked_list_type));
   new_child->process = q;
   new_child->link = NULL;
	/* record the parent's index p in PCB[q] */
   pcb[q].parent = p;
	/* initialize the list of children of PCB[q] as empty (NULL) */
   pcb[q].children = NULL;
	/* create a new link containing the child's index q and 
	appends the link to the end of the linked list of PCB[p] */
   if(pcb[p].children == NULL)
   {
      pcb[p].children = new_child;
      num_children = 1;
   }
   else
   {
      next_child = pcb[p].children;
      num_children=2;
      while(next_child->link != NULL)
      {
         next_child = next_child->link;
         num_children++;
      }
      next_child->link = new_child;
   }
	/* print message: cr[p]	creates nth child of PCB[p] at PCB[q] */
   if(num_children == 1)
   {
      printf("\ncr[%d]  /*creates %dst child of PCB[%d] at PCB[%d]*/",p,num_children,p,q); 
   }
   if(num_children == 2)
   {
      printf("\ncr[%d]  /*creates %dnd child of PCB[%d] at PCB[%d]*/",p,num_children,p,q); 
   }
   if(num_children == 3)
   {
      printf("\ncr[%d]  /*creates %drd child of PCB[%d] at PCB[%d]*/",p,num_children,p,q); 
   }
   if(num_children > 3)
   {
      printf("\ncr[%d]  /*creates %dth child of PCB[%d] at PCB[%d]*/",p,num_children,p,q); 
   }
   
	return;
}

/***************************************************************/
void optionThreeRecursion(linked_list_type *genericName) //(takes as parameter a variable of linked list type)
{
	/* declare local vars */
   int q;
	/* if node parameter passed is NULL, return */
   if(genericName == NULL)
   {
      return;
   }
	/* else recursively call this procedure on node's link field */
   else
   {
      optionThreeRecursion(genericName->link);
   	/* set q to node's process field */
      q = genericName->process;
   	/* recursively call this procedure on pcb[q]'s children field */
      optionThreeRecursion(pcb[q].children);
   	/* print message of PCB[q] deleted */
      printf("PCB[%d]",q);
   	/* free memory allocated by the node parameter */
      free(genericName);
   	/* set pcb[q]'s parent to -1 */
      pcb[q].parent = -1;
   	/* set node paramter to NULL */
      genericName = NULL;
   }
	return;
}

/***************************************************************/
void optionThree() 
{
	/* delcare local vars */
	int parent;
	/* prompt for parent process p */
   printf("\nEnter the process whose descendants are to be destroyed: ");
   scanf("%d", &parent);
   printf("%d", parent);
	/* print message of descendants to be destroyed */
   printf("\nde[%d]    /* destroys all descendants of PCB[%d] which includes: \n",parent,parent);
	/* call OPTION 3 recursive procedure on pcb[p]'s children */
   optionThreeRecursion(pcb[parent].children);
   printf("   */");
	/* set pcb[p]'s children to NULL */
   pcb[parent].children = NULL;
	return;
}

/***************************************************************/
void optionFour() 
{
   if(pcb != NULL)
   {
      if(pcb[0].children != NULL)
      {
         optionThreeRecursion(pcb[0].children);
      }
   }
   free(pcb);
	return;
}

/***************************************************************/
int main() 
{
	/* Declare local var's */
   int userInput = -1;
   /* Until user quits */
	/* print menu of options, prompt for user input, and select appropriate option */
	while(userInput != 4)
    {
        printf("\nProcess creation and destruction");
        printf("\n-------------------------------------");
        printf("\n1) Enter parameters\n2) Create a new child process\n3) Destroy all descendants of a process\n4) Quit program and free memory");
        printf("\n\nEnter selection: ");
        scanf("%d", &userInput);
        printf("%d", userInput);
        if(userInput == 1)
        {
            optionOne();
        }
        if(userInput ==2)
        {
            optionTwo();
        }
        if(userInput == 3)
        {
            optionThree();
        }
    }
    optionFour();

   return 1;

}