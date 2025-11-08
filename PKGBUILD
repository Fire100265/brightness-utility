pkgname=brightness-utility
pkgver=1.0
pkgrel=1
pkgdesc=" A simple ddcutil and Qt6 based brightness utility. "
arch=("x86_64")
url="https://github.com/Fire100265/brightness-utility"
license=('GPL-3.0-or-later')
depends=(qt6-base qt6-svg ddcutil)
makedepends=(cmake)
source=("git+https://github.com/Fire100265/brightness-utility.git")


build() {
	cd "$srcdir/$pkgname"
	cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="$pkgdir/usr" -DCMAKE_GENERATOR="Unix Makefiles" -B build
	cd build
	make -j${nproc}
}

package() {
	cd "$srcdir/$pkgname/build"
	cmake --install .
}
sha256sums=('SKIP')
