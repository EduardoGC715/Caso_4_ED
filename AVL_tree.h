#include "Chamber.h"
#include<bits/stdc++.h>
using namespace std;
#ifndef AVL_TREE
#define AVL_TREE
class AVL_tree{
private:
    Chamber *root;

    int max_distance;
    int num_chambers;
    int tunnel_ID;
public:
    int height(Chamber *chamber){
        if (chamber != nullptr)
            return chamber->Get_Height();
        return 0;
    }

    int max(int a, int b){
        return (a > b)? a : b;
    }

    Chamber* Right_Rotate(Chamber *to_change){
        Chamber *tc_next_lower = to_change->Get_Next_Lower();
        Chamber *tc_nl_next_higher = tc_next_lower->Get_Next_Higher();

        // Perform rotation
        tc_next_lower->Set_Next_Higher(to_change);
        to_change->Set_Next_Lower(tc_nl_next_higher);

        if(to_change->Get_Parent() != nullptr){
            tc_next_lower->Set_Parent(to_change->Get_Parent());
        }
        else{
            root=tc_next_lower;
            tc_next_lower->Set_Parent(nullptr);
        }
        to_change->Set_Parent(tc_next_lower);
        tc_nl_next_higher->Set_Parent(to_change);

        // Update heights
        to_change->Set_Height(max(height(to_change->Get_Next_Lower()), height(to_change->Get_Next_Higher())) + 1);
        tc_next_lower->Set_Height(max(height(tc_next_lower->Get_Next_Lower()), height(tc_next_lower->Get_Next_Higher())) + 1);

        // Return new root
        return tc_next_lower;
    }

    Chamber* Left_Rotate(Chamber *to_change){
        Chamber *tc_next_higher = to_change->Get_Next_Higher();
        Chamber *tc_nh_next_lower = tc_next_higher->Get_Next_Lower();

        // Perform rotation
        tc_next_higher->Set_Next_Lower(to_change);
        to_change->Set_Next_Higher(tc_nh_next_lower);

        if(to_change->Get_Parent() != nullptr){
            tc_next_higher->Set_Parent(to_change->Get_Parent());
        }
        else{
            tc_next_higher->Set_Parent(nullptr);
        }
        to_change->Set_Parent(tc_next_higher);
        tc_nh_next_lower->Set_Parent(to_change);

        // Update heights
        to_change->Set_Height(max(height(to_change->Get_Next_Lower()), height(to_change->Get_Next_Higher())) + 1);
        tc_next_higher->Set_Height( max(height(tc_next_higher->Get_Next_Lower()), height(tc_next_higher->Get_Next_Higher())) + 1);

        // Return new root
        return tc_next_higher;
    }

    int Get_Balance(Chamber *to_check){
        if (to_check == nullptr)
            return 0;
        return height(to_check->Get_Next_Lower()) - height(to_check->Get_Next_Higher());
    }


    Chamber* Smart_Insert(Chamber chamber_to_insert){
        return Insert(root,chamber_to_insert);
    }

    Chamber* Insert(Chamber *chamber_to_check ,Chamber chamber_to_insert){
        /* 1. Perform the normal BST insertion */
        if (chamber_to_check != nullptr){
            if (chamber_to_insert.Get_Potential() < chamber_to_check->Get_Potential()){
                chamber_to_check->Set_Next_Lower(Insert(chamber_to_check->Get_Next_Lower(), chamber_to_insert));
            }
            else if (chamber_to_insert.Get_Potential() > chamber_to_check->Get_Potential()){
                chamber_to_check->Set_Next_Higher(Insert(chamber_to_check->Get_Next_Higher(), chamber_to_insert));
            }
            return chamber_to_check;
        }
        chamber_to_check = &chamber_to_insert;
        return chamber_to_check;

        /* 2. Update height of this ancestor Chamber */
        chamber_to_check->Set_Height(1 + max(height(chamber_to_check->Get_Next_Lower()), height(chamber_to_check->Get_Next_Higher())));

        /* 3. Get the balance factor of this ancestor
            Chamber to check whether this Chamber became
            unbalanced */
        int balance = Get_Balance(chamber_to_check);

        // If this Chamber becomes unbalanced, then
        // there are 4 cases

        // Left Left Case
        if (balance > 1 && chamber_to_insert.Get_Potential() < chamber_to_check->Get_Next_Lower()->Get_Potential())
            return Right_Rotate(chamber_to_check);

        // Right Right Case
        if (balance < -1 && chamber_to_insert.Get_Potential() > chamber_to_check->Get_Next_Higher()->Get_Potential())
            return Left_Rotate(chamber_to_check);

        // Left Right Case
        if (balance > 1 && chamber_to_insert.Get_Potential() > chamber_to_check->Get_Next_Lower()->Get_Potential())
        {
            chamber_to_check->Set_Next_Lower(Left_Rotate(chamber_to_check->Get_Next_Lower()));
            return Right_Rotate(chamber_to_check);
        }

        // Right Left Case
        if (balance < -1 && chamber_to_insert.Get_Potential() < chamber_to_check->Get_Next_Higher()->Get_Potential())
        {
            chamber_to_check->Set_Next_Higher(Right_Rotate(chamber_to_check->Get_Next_Higher()));
            return Left_Rotate(chamber_to_check);
        }

        /* return the (unchanged) Chamber pointer */
        return chamber_to_check;
    }
    void Smart_Pre_Order(){
        Pre_Order(root);
    }

    void Pre_Order(Chamber* root)
    {
        if(root != NULL)
        {
            cout << root->Get_Potential() << " ";
            Pre_Order(root->Get_Next_Lower());
            Pre_Order(root->Get_Next_Higher());
        }
    }
};

#endif
