#pragma once

#include <utility>
#include <memory>

template <typename T>
class GridDeque {
 private:
  using TArray = T*;
  size_t nrows;  // 행 개수
  size_t ncols;  // 열 개수

  std::size_t numRows;
  TArray elems;  // 데이터 요소를 저장하는 배열
  T* hdPtr;      // 덱의 첫 번째 요소를 가리키는 포인터
  T* tlPtr;       // 덱의 다음 위치를 가리키는 포인터

 public:
  // 생성자: 행과 열의 크기를 받아서 초기화
  GridDeque(size_t nrows, size_t ncols) 
    : nrows(nrows), ncols(ncols), numRows{0} {
    // 요소를 저장하는 배열 할당
    elems = new T[nrows * ncols];
    // 초기 상태에서 hdPtr와 tlPtr는 배열의 시작 위치를 가리킴
    hdPtr = elems;
    tlPtr = elems;
  }

  // 소멸자: 동적으로 할당된 메모리 해제
  ~GridDeque() {
    delete[] elems;
  }
                     // 덱의 맨 앞에서 요소를 제거하는 함수
  void PopFront() {
    if (numRows == 0) {
      throw std::exception("GridDeque is empty!");
    }
    hdPtr += ncols;
    if (hdPtr >= elems + nrows * ncols) 
      hdPtr = elems;

    numRows--;
  }

   //덱의 맨 뒤에 요소를 추가하는 함수
  void PushBack(std::initializer_list<T> ilist) {
    if (numRows == nrows) {
      throw std::exception("GridDeque is full!");
    }

    for (const auto& e : ilist) {
      *tlPtr = e;   // tlPtr 위치에 요소 추가
      ++tlPtr;      // tlPtr를 다음 위치로 이동
    }

    // 배열의 끝을 넘어갔을 경우, 처음으로 되돌아감
    if (tlPtr >= elems + (nrows * ncols)) 
      tlPtr = elems;

    numRows++;
  }


    // 특정 행과 열에 있는 요소에 접근하는 함수
  T& At(size_t row, size_t col) {
    // 유효하지 않은 행 또는 열 인덱스인 경우 에러 메시지 출력하고 종료
    if (row >= nrows || col >= ncols) {
      throw std::out_of_range("GridDeque: Out of bounds!");
    }

    std::uintptr_t startAddress = 
      reinterpret_cast<std::uintptr_t>(elems);
    std::uintptr_t endAddress =
        reinterpret_cast<std::uintptr_t>(elems + (nrows * ncols));
    std::uintptr_t atAddress =
        reinterpret_cast<std::uintptr_t>(hdPtr + ((row * ncols) + col));

    if (endAddress <= atAddress) {
      std::uintptr_t diff = atAddress - endAddress;
      atAddress = startAddress + diff;
    }

    T* at = reinterpret_cast<T*>(atAddress);
    
    return *at;  // 해당 위치의 요소 반환
  }

  bool IsFull() { return numRows == nrows; }

  // 덱이 비어 있는지 여부를 반환하는 함수
  bool IsEmpty() { return numRows == 0; }
};