/*************************************************************
 * 1. Name:
 *      Hayley Branchflower  & Graham McClure
 * 2. Module
 *      WALLET
 * 3. Assignment Description:
 *      A class to represent an wallet with multiple credit cards
 **************************************************************/

#pragma once

#include <cassert>

class TestWallet;

 /************************************
  * WALLET
  ************************************/
class Wallet
{
      friend TestWallet;
private:
   double accountSam;
   double accountSue;
   double* pCurrentAccount;

public:
   // Constructors
   Wallet() : accountSam{0.0}, accountSue{0.0}, pCurrentAccount{&accountSam} {};
   
   // Setters
   void updateSam(double amount)
   {
      accountSam += amount;
   };
   void updateSue(double amount)
   {
      accountSue += amount;
   };
   void updateCurrent(double amount)
   {
      *pCurrentAccount += amount;
   };
   
   void chooseSam()
   {
      pCurrentAccount = &accountSam;
   };
   void chooseSue()
   {
      pCurrentAccount = &accountSue;
   };
   void chooseCurrent()
   {
      if (accountSam > accountSue)
      {
         chooseSam();
      }
      else
      {
         chooseSue();
      }
   };
   
   // Getters
   double getSam()const       { return accountSam; };
   double getSue()const       { return accountSue; };
   double getCurrent()const   { return *pCurrentAccount; };
};

