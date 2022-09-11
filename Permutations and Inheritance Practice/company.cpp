#include "company.hpp"
using namespace std;
// Initializes the tracker with n students and their 1-person companies.
CompanyTracker::CompanyTracker(int n)
{
  numCompanies = n;
  companies = new Company* [numCompanies];
  for (int i = 0; i < numCompanies; ++i){
      companies[i] = new Company ();
  }
}

// Deallocates all dynamically allocated memory.
CompanyTracker::~CompanyTracker()
{//make sure everything is split
  // your implementation goes here
  for (int i = 0; i < numCompanies; i++){
      delete companies[i];
  }
  delete [] companies;
}

void CompanyTracker::merge(int i, int j)
{
  // your implementation goes here
  if (i == j) return;
  if ((i < 0) || (i >= numCompanies)) return;
  if ((j < 0) || (j >= numCompanies)) return;
  if (inSameCompany(i, j)) return;
  Company* banana= new Company(largestCompany(i), largestCompany(j));
  largestCompany(i)->parent = banana;
  largestCompany(j)->parent = banana;
  return;
}

void CompanyTracker::split(int i)
{
  // your implementation goes here
  if ((i < 0) || (i >= numCompanies)) return;
  if (largestCompany(i)->merge1 == nullptr) return;
  Company* bankrupt = largestCompany(i);
  bankrupt->merge1->parent = nullptr;
  bankrupt->merge2->parent = nullptr;
  delete bankrupt;
  return;
}

bool CompanyTracker::inSameCompany(int i, int j)
{
  // your implementation goes here
  if (i == j) return true;
    else if ((i < 0) || (i >= numCompanies)) return false;
      else if ((j < 0) || (j >= numCompanies)) return false;
        else if (largestCompany(i) == largestCompany(j)) return true;
          else return false;
}

Company* CompanyTracker::largestCompany(int i)
{
  if (companies[i]->parent == nullptr) return companies[i];
  Company* biggest = companies[i];
  while (biggest->parent != nullptr)
  {
    biggest = biggest->parent;
  }
   return biggest;
}