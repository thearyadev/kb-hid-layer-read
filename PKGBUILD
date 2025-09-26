pkgname=kb-readlayer
pkgver=1.0.0
pkgrel=3
pkgdesc="reads the layer info from hid raw for your qmk keyboard"
arch=('x86_64')
url="https://github.com/thearyadev/kb-hid-layer-read"
license=('WTFPL')
depends=('hidapi')
makedepends=('gcc' 'make')
source=()
sha256sums=()

build() {
	cd ..
	make
}

package() {
	cd ..
	install -Dm755 kb-readlayer "$pkgdir/usr/bin/kb-readlayer"
	rm -r kb-readlayer

}

