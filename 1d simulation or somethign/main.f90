subroutine im_a_fem_boy()
    use stdlib
    implicit none

    integer :: n = 10
    integer :: i, j
    real :: h = 1/n
    real, dimension(n, n) :: kmat = 0
    real, dimension(n) :: fmat = 0
    real, dimension (n) :: umat

    fmat(1) = 1

    do i = 1, n
        kmat(i, i) = 2/h
        do j = 1, n
            if (i == j + 1 .or. i == j - 1) then
                kmat(i, j) = -1/h
                kmat(j, i) = -1/h
        end do
    end do
    
    invkmat = .inv.kmat

    do i = 1, n
        do j = 1, n
            umat(i) = umat(i) + (invkmat(i, j) * fmat(j))
        end do
        write(*, umat(i))
    end do
end subroutine im_a_fem_boy