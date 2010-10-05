file = [IPTG_compound.xml]

MoDeL
{
	species id = [IPTG_compound], name = [IPTG compound itself]
	{
		interface
		{
			url:[http://2010.igem.org/Team:USTC_Software];
			shortDesc:[species contains only the compound of IPTG];
		}
		cnModel
		{
			listOfChains
			{
				chain
				{
					listOfParts
					{
						part
						{
							partReference:[IPTG];
							partLabel:[IPTG];
							partType:[Compound];
							partCategory:[compound];
						}
					}
				}
			}
			listOfTrees
			{
			}
		}
		listOfReferencedReactions
		{
			referencedReaction:[bid_IPTG_lacI153_4] speciesType = [reactant];
		}
	}
}
