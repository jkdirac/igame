file = [anyub_forwardrna.xml]

MoDeL
{
	species id = [anyub_forwardrna], name = [any unbinded forward RNA]
	{
		interface
		{
			url:[http://2010.igem.org/Team:USTC_Software];
			shortDesc:[species template for any forward RNA unbinded];
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
							partReference:[ANYUB];
							partLabel:[ANYUB];
							partType:[FowardRNA];
							partCategory:[substituent];
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
			referencedReaction:[tm_degradation] speciesType = [reactant];
		}
	}
}

