class Area():
    def __init__(self, name):
        self.name = name
        self.has_bts = False
        self.has_sig = False
        self.prior_pairs = []  # pair area obj
        self.next_pairs = []

def get_next_pairs_for_area(area_name, areas, pairs):
    for pair in pairs:
        if area_name in pair:
            pa = pair[0] if area_name == pair[1] else pair[1]
            areas[area_name].next_pairs.append(areas[pa])
            areas[pa].prior_pairs.append(areas[area_name])
            pair.pop()
            pair.pop()
    return areas[area_name].next_pairs

def get_data(line):
    areas = {}  # area_name:area_obj
    pairs = []
    infos = line.split()
    area_num = int(infos[0])
    next_pairs = []
    for i in range(0, len(infos[1:]), 2):
        pairs.append([int(infos[1:][i]), int(infos[1:][i + 1])])
    for name in range(area_num):
        areas[name + 1] = Area(name + 1)
    for ar_name in areas:
        if areas[ar_name].next_pairs or areas[ar_name].prior_pairs:
            continue
        next_pairs = get_next_pairs_for_area(ar_name, areas, pairs)
        while next_pairs:
            next_nextpairs = []
            for next_pa in next_pairs:
                next_nextpairs += get_next_pairs_for_area(next_pa.name, areas, pairs)
            next_pairs = next_nextpairs
    for area in areas.values():
        if not area.next_pairs and len(area.prior_pairs) == 1 and not area.prior_pairs[0].has_bts:
            deploy_a_bts(area.prior_pairs[0])
    return areas.values()

def deploy_a_bts(area_obj):
    if area_obj.has_bts:
        raise AssertionError("Duplicated building BTS!")
    area_obj.has_bts = True
    area_obj.has_sig = True
    for pa in area_obj.prior_pairs:
        if not pa.has_sig: pa.has_sig = True
    for pa in area_obj.next_pairs:
        pa.has_sig = True

def benefit_when_area_has_bts(iarea):
    n_no_sig = 0
    for ar in ([iarea] + iarea.prior_pairs + iarea.next_pairs):
        if not ar.has_sig:
            n_no_sig += 1
    return n_no_sig

def _deploy_bts_for_a_area_chain(start_area):
    nbts = 0
    curr_area = start_area
    curr_level = [curr_area]
    next_level = []
    processed_area = []
    while curr_level:
        for curr_area in curr_level:
            if curr_area in processed_area:
                continue
            processed_area.append(curr_area)
            if not curr_area.has_bts:
                # build bts in the area who has prior with no sig and its the only next unprocessed pair for this prior
                for pri_pa in curr_area.prior_pairs:
                    if not pri_pa.has_sig:
                        for pri_pa_next_pa in pri_pa.next_pairs:
                            if pri_pa_next_pa not in processed_area:
                                break
                        else:
                            deploy_a_bts(curr_area)
                            nbts += 1
                            break
            if not curr_area.has_sig:
                # build bts in the area whose next pairs all has sig without bts
                for next_pa in curr_area.next_pairs:
                    if not next_pa.has_sig:
                        break
                else:
                    if curr_area.next_pairs:
                        deploy_a_bts(curr_area)
                        nbts += 1
            if not curr_area.has_bts:
                # When the area whose next pair has no next, compare benefits bwt this area and its next and the next pair's prior
                for next_pa in curr_area.next_pairs:
                    if not next_pa.next_pairs and not next_pa.has_sig:
                        benefits = [[benefit_when_area_has_bts(curr_area), curr_area]]
                        for next_pa_pri_pa in next_pa.prior_pairs:
                            if next_pa_pri_pa == curr_area:
                                continue
                            bft = [benefit_when_area_has_bts(next_pa_pri_pa), next_pa_pri_pa]
                            benefits.append(bft)
                        benefits.sort(key=lambda x:x[0])
                        best_prior = [benefits[-1][0], benefits[-1][1]]
                        next_pa_benifit = [benefit_when_area_has_bts(next_pa), next_pa]
                        deploy_area = next_pa_benifit[1] if next_pa_benifit[0] >= best_prior[0] else best_prior[1]
                        deploy_a_bts(deploy_area)
                        nbts += 1
            next_level += curr_area.next_pairs
        curr_level = next_level
        next_level = []
    return nbts

def reset_a_area_chain(start_area):
    curr_area = start_area
    curr_level = [curr_area]
    while curr_level:
        next_level = []
        for curr_area in curr_level:
            curr_area.has_bts = False
            curr_area.has_sig = False
            for ar in curr_area.next_pairs:
                if ar not in next_level:
                    next_level.append(ar)
        curr_level = next_level

def is_more_than_one_bts_in_current_area_and_pairs(curr_area):
    nbts = 0
    if curr_area.has_sig:
        pairs = [curr_area] + curr_area.next_pairs + curr_area.prior_pairs
        for iarea in pairs:
            if iarea.has_bts:
                nbts += 1
            if nbts > 1:
                return
    return False

def check_a_deployed_chain(start_area):
    nbts_remove = 0
    curr_area = start_area
    curr_level = [curr_area]
    while curr_level:
        next_level = []
        for curr_area in curr_level:
            if curr_area.has_bts:
                pairs = curr_area.next_pairs + curr_area.prior_pairs + [curr_area]
                for iarea in pairs:
                    if not is_more_than_one_bts_in_current_area_and_pairs(iarea):
                        break
                else:
                    curr_area.has_bts = False
                    nbts_remove += 1
            for ar in curr_area.next_pairs:
                if ar not in next_level:
                    next_level.append(ar)
        curr_level = next_level
    return nbts_remove

def count_a_chain_bts(start_area):
    nbts = 0
    curr_area = start_area
    curr_level = [curr_area]
    checked_area = []
    while curr_level:
        next_level = []
        checked_area += curr_level[:]
        for curr_area in curr_level:
            if curr_area.has_bts:
                nbts += 1
            for ar in curr_area.next_pairs:
                if ar not in checked_area:
                    next_level.append(ar)
        curr_level = next_level
    return nbts

def deploy_bts_for_a_area_chain(start_area):
    try_list = [start_area] + start_area.next_pairs[:] 
    try_results = []    
    for iarea in try_list:
        if not iarea.has_bts:
            deploy_a_bts(iarea)
        _deploy_bts_for_a_area_chain(start_area)
        check_a_deployed_chain(start_area)
        try_results.append(count_a_chain_bts(start_area))
        reset_a_area_chain(start_area)
    try_results.sort()
    return try_results[0]

def deploy_bts(areas):
    nbts = 0
    for ar in areas:
        if ar.prior_pairs:
            continue
        if not ar.next_pairs and not ar.prior_pairs:
            ar.has_bts = True
            ar.has_sig = True
            nbts += 1
            continue
        if not ar.prior_pairs and ar.next_pairs:
            nbts += deploy_bts_for_a_area_chain(ar)
    return nbts
        
def read_and_process_input_file(input_file, output_file="result.txt"):
    """ Read from input file and fetch data"""
    case_id = 0
    with open(input_file) as f_input, open(output_file, "w+") as f_output:
        for line in f_input:
            if " " not in line.strip():
                continue
            case_id += 1
            areas = get_data(line)
            nbts = deploy_bts(areas)
            res = "Case #%d: %d\n" % (case_id, nbts)
            print res
            f_output.write(res)
            
if __name__ == "__main__":
    print "start"
    read_and_process_input_file("bts_deployment_small_1497322836350")
