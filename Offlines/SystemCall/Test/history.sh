# For qemu

echo 1
echo 2 
echo 3 
echo 4 
!! # 4
!! 4 # 1
!! 3 # 3
!! 6 # 1
!! 5 # 3
!! # 3
!! # 3
!! 4 # 1

# For sh

echo 1
echo 2 
echo 3 
echo 4 
!! # 4
!-4 # 1
!-3 # 3
!-6 # 1
!-5 # 3
!! # 3
!! # 3
!-4 # 1