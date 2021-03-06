// query_engine_tests.h
#ifndef CYCLUS_TESTS_QUERY_ENGINE_TESTS_H_
#define CYCLUS_TESTS_QUERY_ENGINE_TESTS_H_

#include <gtest/gtest.h>

#include "query_engine.h"

class TestQueryEngine : public QueryEngine {

 public:
  static char separator;
  TestQueryEngine(const std::string snippet){
    size_t found=snippet.find_first_of(separator);
    if (snippet.begin() == found) {
      snippet = snippet.substr(found+1);
      found = snippet.find_first_of(separator);
      
      if (string::npos != found) {
	name_ = snippet.substr(0,found-1);
	content_ = snippet.substr(found);
      }
      else {
	name_ = snippet;
	content_ = "noContent";
      }
    }
    else {
      name_ = "badSnippetName";
      content_ = "badSnippetContent";
    }
  }

  ~TestQueryEngine();
  
  virtual int NElementsMatchingQuery(std::string query) {
    if (query == name_)
      return 1;
    else
      return 0;
  }

  virtual std::string GetElementContent(std::string query, int index = 0) {
    if (query == name_)
      return content_;
    else
      return "failedMatchContent";
	
  }

  virtual std::string GetElementName(std::string query, int index = 0) {
    if (query == name_)
      return name_;
    else if (query == "*")
      return name_;
    else
      return "failedMatchName";
  }

 protected:
  virtual QueryEngine* GetEngineFromSnippet(std::string snippet) {
    return new TestQueryEngine(snippet);
  }

 private:
  std::string content_, name_;

}

class QueryEngineTests  : public ::testing::Test {

 protected:
  QueryEngine *pqe;

  virtual void SetUp() {
    pqe = new TestQueryEngine(":path:to:data:here");
  }

  virtual void TearDown() {
    delete pqe;
  }
  


};

#endif  // CYCLUS_TESTS_QUERY_ENGINE_TESTS_H_
