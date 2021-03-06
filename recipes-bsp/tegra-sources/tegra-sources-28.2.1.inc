SRC_URI = "http://developer.download.nvidia.com/embedded/L4T/r28_Release_v2.1/public_sources.tbz2;downloadfilename=public_sources-28.2.1.tbz2"
SRC_URI[md5sum] = "acb7d00138e94a43f8f91e67008c8533"
SRC_URI[sha256sum] = "0b62f11a811e469f5320d250924a0fa6c6c938d428822559138ebd1c37897098"

unpack_tar_in_tar() {
    cd ${WORKDIR}
    tar -x -j -f ${SRC_ARCHIVE} ${TEGRA_SRC_SUBARCHIVE} --to-command="tar -x -j --no-same-owner -f-"
}

python do_unpack() {
    src_uri = (d.getVar('SRC_URI', True) or "").split()
    rootdir = d.getVar('WORKDIR', True)
    p_dir = os.path.join(d.getVar('S', True), 'patches')
    bb.utils.remove(p_dir, True)
    try:
        fetcher = bb.fetch2.Fetch(src_uri, d)
        urldata = fetcher.ud[src_uri[0]]
        urldata.setup_localpath(d)
    except bb.fetch2.BBFetchException as e:
        raise bb.build.FuncFailed(e)

    d.setVar('SRC_ARCHIVE', urldata.localpath)
    bb.build.exec_func("unpack_tar_in_tar", d)
}

COMPATIBLE_MACHINE = "(tegra186)"
PACKAGE_ARCH = "${SOC_FAMILY_PKGARCH}"
