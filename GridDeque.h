#pragma once

#include <utility>
#include <memory>

template <typename T>
class GridDeque {
 private:
  using TArray = T*;
  size_t nrows;  // �� ����
  size_t ncols;  // �� ����

  std::size_t numRows;
  TArray elems;  // ������ ��Ҹ� �����ϴ� �迭
  T* hdPtr;      // ���� ù ��° ��Ҹ� ����Ű�� ������
  T* tlPtr;       // ���� ���� ��ġ�� ����Ű�� ������

 public:
  // ������: ��� ���� ũ�⸦ �޾Ƽ� �ʱ�ȭ
  GridDeque(size_t nrows, size_t ncols) 
    : nrows(nrows), ncols(ncols), numRows{0} {
    // ��Ҹ� �����ϴ� �迭 �Ҵ�
    elems = new T[nrows * ncols];
    // �ʱ� ���¿��� hdPtr�� tlPtr�� �迭�� ���� ��ġ�� ����Ŵ
    hdPtr = elems;
    tlPtr = elems;
  }

  // �Ҹ���: �������� �Ҵ�� �޸� ����
  ~GridDeque() {
    delete[] elems;
  }
                     // ���� �� �տ��� ��Ҹ� �����ϴ� �Լ�
  void PopFront() {
    if (numRows == 0) {
      throw std::exception("GridDeque is empty!");
    }
    hdPtr += ncols;
    if (hdPtr >= elems + nrows * ncols) 
      hdPtr = elems;

    numRows--;
  }

   //���� �� �ڿ� ��Ҹ� �߰��ϴ� �Լ�
  void PushBack(std::initializer_list<T> ilist) {
    if (numRows == nrows) {
      throw std::exception("GridDeque is full!");
    }

    for (const auto& e : ilist) {
      *tlPtr = e;   // tlPtr ��ġ�� ��� �߰�
      ++tlPtr;      // tlPtr�� ���� ��ġ�� �̵�
    }

    // �迭�� ���� �Ѿ�� ���, ó������ �ǵ��ư�
    if (tlPtr >= elems + (nrows * ncols)) 
      tlPtr = elems;

    numRows++;
  }


    // Ư�� ��� ���� �ִ� ��ҿ� �����ϴ� �Լ�
  T& At(size_t row, size_t col) {
    // ��ȿ���� ���� �� �Ǵ� �� �ε����� ��� ���� �޽��� ����ϰ� ����
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
    
    return *at;  // �ش� ��ġ�� ��� ��ȯ
  }

  bool IsFull() { return numRows == nrows; }

  // ���� ��� �ִ��� ���θ� ��ȯ�ϴ� �Լ�
  bool IsEmpty() { return numRows == 0; }
};