#include <vector>
#include <stdio.h>
#include "pack109.hpp"
#include <iostream>
#include <bitset>
#include <cmath>
 

using namespace std;


void pack109::printVec(vec &bytes) {
  printf("[ ");
  for (int i = 0; i < bytes.size(); i++) {
    printf("0x%x, ", bytes[i]);
  }
  printf("]\n");
}

vec slice(vec& bytes, int vbegin, int vend) {
  auto start = bytes.begin() + vbegin;
  auto end = bytes.begin() + vend + 1;
  vec result(vend - vbegin + 1);
  copy(start, end, result.begin());
  return result;
}

vec pack109::serialize(bool item) {
  vec bytes;
  if (item == true) {
    bytes.push_back(PACK109_TRUE);
  } else {
    bytes.push_back(PACK109_FALSE);
  }
  return bytes;
}

bool pack109::deserialize_bool(vec bytes) {
  if (bytes.size() < 1) {
     throw;
  }

  if (bytes[0] == PACK109_TRUE) {
    return true;
  } else if (bytes[0] == PACK109_FALSE) {
    return false;
  } else {
    throw;
  }

}

vec pack109::serialize(u8 item) {
  vec bytes;
  bytes.push_back(PACK109_U8);
  bytes.push_back(item);
  return bytes;
}

u8 pack109::deserialize_u8(vec bytes) {
  if (bytes.size() < 2) {
    throw;
  }
  if (bytes[0] == PACK109_U8) {
    return bytes[1];
  } else {
    throw;
  }
}

vec pack109::serialize(u32 item) {
  vec bytes;
  u32 itemRtrn; 
  int max = 0x7FFFFFFF;

  if(bytes.size() > max) {
    throw;
  }
  else {
    bytes.push_back(PACK109_U32);
    for(int i = 0; i < 4; i++) {
      itemRtrn = (item >> i * 8);    //what the fuck? 
      bytes.insert(bytes.begin() + 1, itemRtrn);
    }
  }
  return bytes;
}

//Fix this one 
u32 pack109::deserialize_u32(vec bytes) {
  u32 value = 0x00000000;
  if (bytes.size() < 2) {
    throw;
  }

  if(bytes[0] != PACK109_U32) {
    throw; 
  }

  for (auto i = bytes.begin(); i < bytes.end(); i++) {
    value <<= 8;
    value |= *i;
  }

  return value;

}

vec pack109::serialize(u64 item) {
  vec bytes;
  u64 itemRtrn; 
  u64 max = 0xffffffffffffffffL;

  if(bytes.size() > max) {
    throw;
  }
  else {
    bytes.push_back(PACK109_U64);
    for(int i = 0; i < 8; i++) {
      itemRtrn = ((item >> i * 8));
      bytes.insert(bytes.begin() + 1, itemRtrn);
    }
  }
  return bytes;
}

u64 pack109::deserialize_u64(vec bytes) {
  u64 value = 0x0000000000000000;
  if (bytes.size() < 2) {
    throw;
  }

  if(bytes[0] != PACK109_U64) {
    throw; 
  }


  for (auto i = bytes.begin(); i < bytes.end(); i++) {
    value <<= 8;
    value |= *i;   
  }

  return value;
}

//The signed 
vec pack109::serialize(i8 item) {
  vec bytes;
  bytes.push_back(PACK109_I8);
  bytes.push_back(item);
  return bytes;
}

i8 pack109::deserialize_i8(vec bytes) {
  if (bytes.size() < 2) {
    throw;
  }
  if (bytes[0] == PACK109_I8) {
    return bytes[1];
  } 
  else {
    throw;
  }
}

vec pack109::serialize(i32 item) {
  vec bytes;
  i32 itemRtrn; 
  int max = 0x7FFFFFFF;

  if(bytes.size() > max) {
    throw;
  }
  else {
    bytes.push_back(PACK109_I32);
    for(int i = 0; i < 4; i++) {
      itemRtrn = ((item >> i * 8));
      bytes.insert(bytes.begin() + 1, itemRtrn);
    }
  }
  return bytes;
}

i32 pack109::deserialize_i32(vec bytes) {
  i32 value = 0x00000000;
  if (bytes.size() < 2) {
    throw;
  }

  if(bytes[0] != PACK109_I32) {
    throw; 
  }

  for (auto i = bytes.begin()+1; i < bytes.end(); i++) {
    value <<= 8;
    value |= *i;
  }

  return value;
}

vec pack109::serialize(i64 item) {
  vec bytes;
  i64 itemRtrn; 
  i64 max = 0xffffffffffffffffL;

  if(bytes.size() > max) {
    throw;
  }
  else {
    bytes.push_back(PACK109_I64);
    for(int i = 0; i < 8; i++) {
      itemRtrn = ((item >> i * 8));
      bytes.insert(bytes.begin() + 1, itemRtrn);
    }
  }
  return bytes;
}

i64 pack109::deserialize_i64(vec bytes) {
  i64 value = 0x0000000000000000;
  if (bytes.size() < 2) {
    throw;
  }

  if(bytes[0] != PACK109_I64) {
    throw; 
  }

  for (auto i = bytes.begin(); i < bytes.end(); i++) {
    value <<= 8;
    value |= *i;   
  }

  return value;
}

//Floats 

vec pack109::serialize(f32 item) {
  vec bytes;
  int max = 0x7FFFFFFF;
  int intRepresentation = *((int*) &item);

  if(bytes.size() > max) {
    throw;
  }
  else {
    bytes.push_back(PACK109_F32);
    for(int i = 0; i < 4; i++) {
      bytes.insert(bytes.begin() + 1, intRepresentation);
      intRepresentation = intRepresentation >> 8;
    }
  }
  return bytes;
}

f32 pack109::deserialize_f32(vec bytes) {
  u32 temp = 0x00000000;
  f32 value = 0x0000000;
  if (bytes.size() < 2) {
    throw;
  }

  if(bytes[0] != PACK109_F32) {
    throw; 
  }

  for (auto i = bytes.begin()+1; i < bytes.end(); i++) {
    temp <<= 8;
    temp |= *i;
  }

  value = *((f32*) &temp);

  return value;
}

vec pack109::serialize(f64 item) {
  vec bytes;
  long max = 0xffffffffffffffffL;

  long longRepresentation = *((long*) &item);

  if(bytes.size() > max) {
    throw;
  }
  else {
    bytes.push_back(PACK109_F64);
    for(int i = 0; i < 8; i++) {
      bytes.insert(bytes.begin() + 1, longRepresentation);
      longRepresentation = longRepresentation >> 8;
    }
  }
  return bytes;
}

f64 pack109::deserialize_f64(vec bytes) {
  u64 temp = 0x0000000000000000;
  f64 value = 0x000000000000000;
  if (bytes.size() < 2) {
    throw;
  }

  if(bytes[0] != PACK109_F64) {
    throw; 
  }

  for (auto i = bytes.begin()+1; i < bytes.end(); i++) {
    temp <<= 8;
    temp |= *i;
  }

  value = *((f64*) &temp);

  return value;
}

//Strings -------------------------------------------->

vec pack109::serialize(string item) {
  vec bytes;
  u8 itemRtrn; 
  int max = 0x7FFFFFFF;

  if(item.length() < 256) {
    bytes.push_back(PACK109_S8);
    bytes.push_back(item.length());
  }
  else {
    bytes.push_back(PACK109_S16);
    for(int i = 0; i < 2; i++) {
        itemRtrn = ((item.length() >> i * 8));
        bytes.insert(bytes.begin() + 1, itemRtrn);
      }
  }

  for(int i = 0; i < item.length(); i++) {
    bytes.push_back(item[i]);
  }

  return bytes;
}

string pack109::deserialize_string(vec bytes) {

  string value = "";
  long stringLimit = (3 + pow(2,16) - 1);

  if (bytes.size() < 3 || bytes.size() > stringLimit) {
    throw;
  }

  if(bytes[0] != PACK109_S8 && bytes[0] != PACK109_S16) {
    throw; 
  }

  if (bytes[0] == PACK109_S8) {
    for(int i = 2; i < bytes.size(); i++) {
      value += bytes[i];
    }
  }

  else {
    for(int i = 3; i < bytes.size(); i++) {
      value += bytes[i];
    }
  }

  return value;
}

//Arrays ---------------------------------------->

vec pack109::serialize(std::vector<u8> item) {
  vec bytes;
  vec temp; 
  u8 itemRtrn; 
  int max = 0x7FFFFFFF;

  if(item.size() < 256) {
    bytes.push_back(PACK109_A8);
    bytes.push_back(item.size());
  }
  else {
    bytes.push_back(PACK109_A16);
    for(int i = 0; i < 2; i++) {
        itemRtrn = ((item.size() >> i * 8));
        bytes.insert(bytes.begin() + 1, itemRtrn);
      }
  }

  for(int i = 0; i < item.size(); i++) {
    bytes.push_back(item[i]);
  }

  return bytes;

}

vec pack109::serialize(std::vector<u64> item) {
  vec bytes;
  vec temp; 
  u8 itemRtrn; 
  int max = 0x7FFFFFFF;

  if(item.size() < 256) {
    bytes.push_back(PACK109_A8);
    bytes.push_back(item.size());
  }
  else {
    bytes.push_back(PACK109_A16);
    for(int i = 0; i < 2; i++) {
        itemRtrn = ((item.size() >> i * 8));
        bytes.insert(bytes.begin() + 1, itemRtrn);
      }
  }


  for(int i = 0; i < item.size(); i++) {
    temp = pack109::serialize(item[i]);
    
    for(int j = 0; j < temp.size(); j++) {
      bytes.push_back(temp[j]);
    }

  }

  return bytes;
}

vec pack109::serialize(std::vector<f64> item) {
  vec bytes;
  vec temp; 
  u8 itemRtrn; 
  int max = 0x7FFFFFFF;

  if(item.size() < 256) {
    bytes.push_back(PACK109_A8);
    bytes.push_back(item.size());
  }
  else {
    bytes.push_back(PACK109_A16);
    for(int i = 0; i < 2; i++) {
        itemRtrn = ((item.size() >> i * 8));
        bytes.insert(bytes.begin() + 1, itemRtrn);
      }
  }


  for(int i = 0; i < item.size(); i++) {
    temp = pack109::serialize(item[i]);
    
    for(int j = 0; j < temp.size(); j++) {
      bytes.push_back(temp[j]);
    }

  }

  return bytes;
}

vec pack109::serialize(std::vector<string> item) {
  vec bytes;
  vec temp; 
  u8 itemRtrn; 
  int max = 0x7FFFFFFF;

  if(item.size() < 256) {
    bytes.push_back(PACK109_A8);
    bytes.push_back(item.size());
  }
  else {
    bytes.push_back(PACK109_A16);
    for(int i = 0; i < 2; i++) {
        itemRtrn = ((item.size() >> i * 8));
        bytes.insert(bytes.begin() + 1, itemRtrn);
      }
  }


  for(int i = 0; i < item.size(); i++) {
    temp = pack109::serialize(item[i]);
    
    for(int j = 0; j < temp.size(); j++) {
      bytes.push_back(temp[j]);
    }

  }

  return bytes;
}

std::vector<u8> pack109::deserialize_vec_u8(vec bytes) {

  std::vector<u8> value;
  long stringLimit = (3 + pow(2,16) - 1);

  if (bytes.size() < 3 || bytes.size() > stringLimit) {
    throw;
  }

  if(bytes[0] != PACK109_A8 && bytes[0] != PACK109_A16) {
    throw; 
  }

  if (bytes[0] == PACK109_A8) {
    for(int i = 2; i < bytes.size(); i++) {
      value.push_back(bytes[i]);
    }
  }

  else {
    for(int i = 3; i < bytes.size(); i++) {
    value.push_back(bytes[i]);   
    }
  }

  return value;
}

std::vector<u64> pack109::deserialize_vec_u64(vec bytes) {

  std::vector<u64> value;
  u64 tempInt = 0;
  vec temp; 
  long stringLimit = (3 + pow(2,16) - 1);

  if (bytes.size() < 3 || bytes.size() > stringLimit) {
    throw;
  }

  if(bytes[0] != PACK109_A8 && bytes[0] != PACK109_A16) {
    throw; 
  }

  if (bytes[0] == PACK109_A8) {
    for(int i = 2; i < bytes.size(); i++) {
      temp.push_back(bytes.at(i));  

      while(++i < bytes.size() && bytes.at(i) != PACK109_U64) {
        temp.push_back(bytes[i]);
      }

      tempInt = pack109::deserialize_u64(temp);
      value.push_back(tempInt);
      
    }
  }

  else {
    for(int i = 3; i < bytes.size(); i++) {
      temp.push_back(bytes.at(i));  

      while(++i < bytes.size() && bytes.at(i) != PACK109_U64) {
        temp.push_back(bytes[i]);
      }

      tempInt = pack109::deserialize_u64(temp);
      value.push_back(tempInt);
      
    }

  }

  return value;

}

std::vector<f64> pack109::deserialize_vec_f64(vec bytes) {
  std::vector<f64> value;
  f64 tempInt = 0;
  vec temp; 
  long stringLimit = (3 + pow(2,16) - 1);

  if (bytes.size() < 3 || bytes.size() > stringLimit) {
    throw;
  }

  if(bytes[0] != PACK109_A8 && bytes[0] != PACK109_A16) {
    throw; 
  }

  if (bytes[0] == PACK109_A8) {
    for(int i = 2; i < bytes.size(); i++) {
      temp.push_back(bytes.at(i));  

      while(++i < bytes.size() && bytes.at(i) != PACK109_F64) {
        temp.push_back(bytes[i]);
      }

      tempInt = pack109::deserialize_f64(temp);
      value.push_back(tempInt);
      
    }
  }

  else {
    for(int i = 3; i < bytes.size(); i++) {
      temp.push_back(bytes.at(i));  

      while(++i < bytes.size() && bytes.at(i) != PACK109_F64) {
        temp.push_back(bytes[i]);
      }

      tempInt = pack109::deserialize_f64(temp);
      value.push_back(tempInt);
      
    }

  }

  return value;
}

std::vector<string> pack109::deserialize_vec_string(vec bytes) {
  std::vector<string> value;
  string tempString = "";
  vec temp; 
  long stringLimit = (3 + pow(2,16) - 1);

  if (bytes.size() < 3 || bytes.size() > stringLimit) {
    throw;
  }

  if(bytes[0] != PACK109_A8 && bytes[0] != PACK109_A16) {
    throw; 
  }

  if (bytes[0] == PACK109_A8) {
    int i = 2; 
    while(i < bytes.size()) {
      temp.push_back(bytes.at(i));  
      i++;
      while(i < bytes.size() && bytes.at(i) != PACK109_S8 && bytes.at(i) != PACK109_S16) {
        temp.push_back(bytes.at(i));
        i++;
      }
      tempString = pack109::deserialize_string(temp);
      value.push_back(tempString);
      temp.clear();
      tempString.clear();
    }
  }

  return value;

}

//Maps 
//String name 
//vector<u8> bytes 
vec pack109::serialize(struct File item) {

    vec bytes;
    vec temp;
    bytes.push_back(PACK109_M8);
    bytes.push_back(1);

    //Making the Key first
    string file = "File";
    temp = pack109::serialize(file);

    for(u8 item : temp) {
        bytes.push_back(item);
    }
    temp.clear();

    bytes.push_back(PACK109_M8);
    bytes.push_back(2);

    //Doing string name now 
    string name = "name";
    temp = pack109::serialize(name);

    for(int i = 0; i < temp.size(); i++) {   //if it doesnt work its because of this 
        bytes.push_back(temp.at(i));
    }
    temp.clear();

    temp = pack109::serialize(item.name);
    for(u8 item : temp) {
      bytes.push_back(item);
    }
    temp.clear();

    //Doing vector<u8> now 
    string b = "bytes";
    temp = pack109::serialize(b);

    for(u8 item : temp) {
        bytes.push_back(item);
    }
    temp.clear();

    temp = pack109::serialize(item.array); //why is this happening??? 
    for(u8 item : temp) {
        bytes.push_back(item);
    }
    temp.clear();
    

    return bytes;

}

vec pack109::serialize(struct Pull item) { 
    vec bytes;
    vec temp;
    bytes.push_back(PACK109_M8);
    bytes.push_back(1);

    //Making the Key first
    string pull = "Request";
    temp = pack109::serialize(pull);

    for(u8 item : temp) {
        bytes.push_back(item);
    }
    temp.clear();

    bytes.push_back(PACK109_M8);
    bytes.push_back(2);

    //Doing string name now 
    string name = "name";
    temp = pack109::serialize(name);

    for(u8 item : temp) {
        bytes.push_back(item);
    }
    temp.clear();

    temp = pack109::serialize(item.name);
    for(u8 item : temp) {
        bytes.push_back(item);
    }
    temp.clear();

    return bytes;

}

struct File pack109::deserialize_file(vec bytes) {

    File file;
    string name;
    vector<u8> array;
    string key;
    vec temp;

    int i = 12;
    while(i < bytes.size()) {
        temp.push_back(bytes[i++]);

        while(i < bytes.size() && bytes[i] != PACK109_S8 && bytes[i] != PACK109_S16 && bytes[i] != PACK109_U8 && bytes[i] != PACK109_F32) {
            temp.push_back(bytes[i]);
            i++;
        }

        //Key section
        key = pack109::deserialize_string(temp);
        temp.clear();

        //String name section
        if(key.compare("name") == 0) {
            temp.push_back(bytes[i++]);

            while(i < bytes.size() && bytes[i] != PACK109_S8) {
                temp.push_back(bytes[i]);
                i++;
            }

            name = pack109::deserialize_string(temp);
        }

        //vecU8 section 
        else if(key.compare("array") == 0) {
            temp.push_back(bytes[i++]);

            while(i < bytes.size() && bytes[i] != PACK109_S8) {
                temp.push_back(bytes[i]);
                i++;
            }

            array = pack109::deserialize_vec_u8(temp);

        }
        temp.clear();
        key.clear();

    }

    file = {name, array};
    return file; 


}