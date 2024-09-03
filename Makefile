# 컴파일러와 플래그 정의
CXX = g++
CXXFLAGS = -Wall -O2 -Iheader  # header 폴더를 포함하도록 -I 플래그 사용

# 소스 파일과 오브젝트 파일
SRCS = main.cpp\
       source/user.cpp\
       source/usermanager.cpp\
       source/product.cpp\
       source/productmanager.cpp\
       source/shoppingmanager.cpp\
	   source/cart.cpp\
	   source/cartmanager.cpp\
	   source/login.cpp\
	   source/loginmanager.cpp\
	   source/mainmenu.cpp

OBJS = $(SRCS:.cpp=.o)

# 실행 파일 이름
TARGET = main.out

# 기본 규칙
all: $(TARGET)

# 링크 단계
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# 개별 소스 파일을 오브젝트 파일로 컴파일
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 청소 규칙
clean:
	rm -f $(OBJS) $(TARGET)
